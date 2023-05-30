/**
 * \file stockserver.c
 * \brief Concurrent stock server implementation (event-driven approach)
 */

#include "csapp.h"
#include "stock.h"
#include "debug.h"

struct client_pool {
    int maxfd;             /**< Maximum file descriptor. */
    fd_set read_set;       /**< Set of read file descriptors. */
    fd_set ready_set;      /**< Set of ready file descriptors. */
    int nready;            /**< Number of ready file descriptors from select. */
    int maxi;              /**< Pool highwater mark. */
    struct client_info {
        int fd;    /**< File descriptor. */
        rio_t rio; /**< Buffered I/O for file descriptor. */
    } clients[FD_SETSIZE]; /**< Array of clients. */
};

struct client_pool pool;
struct stock_item *stock_db;

void echo(int connfd);

void pool_init(struct client_pool *p, int listenfd);
void pool_add_client(struct client_pool *p, int connfd);
void pool_check_clients(struct client_pool *p);

void process_request(struct stock_item *tree, char *buffer);

void pool_init(struct client_pool *p, int listenfd)
{
    p->maxi = -1;
    for (int i = 0; i < FD_SETSIZE; i++)
        p->clients[i].fd = -1;

    p->maxfd = listenfd;

    FD_ZERO(&p->read_set);
    FD_ZERO(&p->ready_set);

    FD_SET(listenfd, &p->read_set);
}

void pool_add_client(struct client_pool *p, int connfd)
{
    debug("adding new client with file descriptor %d...\n", connfd);

    /* Decrease the amount of ready descriptors */
    p->nready--;

    /* Find the empty slot and add the descriptor */
    for (int i = 0; i < FD_SETSIZE; i++) {
        debug("checking if slot %d is empty...\n", i);

        if (p->clients[i].fd < 0) {
            debug("found empty slot at %d\n", i);

            /* Add connected descriptor to the pool */
            p->clients[i].fd = connfd;
            Rio_readinitb(&p->clients[i].rio, connfd);
            FD_SET(connfd, &p->read_set);

            /* Update max descriptor and pool highwater mark */
            p->maxfd = (connfd > p->maxfd) ? connfd : p->maxfd;
            p->maxi = (i > p->maxi) ? i : p->maxi;

            return;
        }
    }

    /* If we reached here, it means we didn't find an empty slot */
    fprintf(stderr, "pool_add_client: too many clients\n");
}

void pool_check_clients(struct client_pool *p)
{
    char buf[MAXLINE] = { '\0' };

    /* Loop through all clients while there is some ready descriptors */
    for (int i = 0; p->nready > 0 && i <= p->maxi; i++) {
        int connfd = p->clients[i].fd;
        rio_t *rio = &p->clients[i].rio;

        /* If the descriptor is ready, process the request */
        if (connfd > 0 && FD_ISSET(connfd, &p->ready_set)) {
            debug("connection descriptor %d is ready\n", connfd);

            p->nready--;

            /* Read the data */
            int n = Rio_readlineb(rio, buf, MAXLINE);
            debug("server read %d bytes\n", n);

            /* If the client closed the connection, remove it from the pool */
            if (n <= 0)
                goto close_client;

            /* Check if the client wants to close the connection */
            if (!strcmp(buf, "exit\n"))
                goto close_client;

            /* Process the request */
            process_request(stock_db, buf);

            /* Write the data back to the client */
            Rio_writen(connfd, buf, strlen(buf));
        }

        /* Proceed to the next client */
        continue;

    close_client:
        Close(connfd);
        FD_CLR(connfd, &p->read_set);
        p->clients[i].fd = -1;
    }
}

void process_request(struct stock_item *tree, char *buffer)
{
    debug("processing request: %s...\n", buffer);

    /* Compare the input to the commands
       Note: This operation is safe, as the input is guaranteed to be
       well-formed as per the project specification. */
    if (!strncmp(buffer, "show", 4)) {
        /* Show the stock information */
        buffer[0] = '\0';

        /* Dump the stock info to the buffer */
        stock_dump(tree, buffer);

        /* Replace newlines with spaces */
        for (int i = 0; buffer[i] != '\0'; i++)
            if (buffer[i] == '\n')
                buffer[i] = ' ';

        /* Replace last space with a newline at the end of the buffer */
        buffer[strlen(buffer) - 1] = '\n';
    } else if (!strncmp(buffer, "buy ", 4)) {
        /* Buy a stock */

        /* Parse the input */
        int id, amount;
        sscanf(buffer, "buy %d %d\n", &id, &amount);

        /* Try buying the stock */
        if (stock_buy(tree, id, amount))
            strcpy(buffer, "[buy] success\n");
        else 
            strcpy(buffer, "[buy] failure\n");
    } else if (!strncmp(buffer, "sell ", 5)) {
        /* Sell a stock */

        /* Parse the input */
        int id, amount;
        sscanf(buffer, "sell %d %d\n", &id, &amount);

        /* Try selling the stock */
        if (stock_sell(tree, id, amount))
            strcpy(buffer, "[sell] success\n");
        else 
            strcpy(buffer, "[sell] failure\n");
    } else if (!strncmp(buffer, "exit\n", 5)) {
        /* Exit from the market */
        
        buffer[0] = '\0';
        return;
    } else {
        /* Invalid command */

        strcpy(buffer, "invalid command\n");
    }
}

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];

    /* Basic command line argument sanity check */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    /* Initialize the stock database */
    debug("initializing stock database...\n");
    stock_db = stock_init("stock.txt");
    stock_print(stock_db);
    
    /* Open listening file descriptor using the given port */
    debug("opening listening file descriptor...\n");
    listenfd = Open_listenfd(argv[1]);

    /* Initialize the client pool */
    debug("initializing client pool...\n");
    pool_init(&pool, listenfd);

    /* Main server loop */
    while (1) {
        /* Update the ready set */
        debug("waiting for ready descriptors...\n");
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);
        debug("found %d ready descriptors\n", pool.nready);
        
        /* If there is a new connection request... */
        if (FD_ISSET(listenfd, &pool.ready_set)) {
            debug("new connection request incoming...\n");

            /* ...accept the request... */
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

            /* ...print the client's IP address and port number... */
            Getnameinfo(
                (SA *)&clientaddr,
                clientlen,
                client_hostname,
                MAXLINE,
                client_port,
                MAXLINE,
                0
            );
            debug("connected to %s:%s\n", client_hostname, client_port);

            /* ...and add the new client to the pool */
            pool_add_client(&pool, connfd);
        }

        /* Check all clients for data */
        pool_check_clients(&pool);

        /* If no clients are connected, save the stock database */
        bool is_connected = false;
        for (int i = 0; i <= pool.maxi; i++) {
            if (pool.clients[i].fd > 0) {
                is_connected = true;
                break;
            }
        }

        if (!is_connected) {
            debug("no clients connected, saving stock database...\n");
            stock_save(stock_db, "stock.txt");
        }
    }

    return 0;
}
