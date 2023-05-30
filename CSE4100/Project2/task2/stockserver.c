/**
 * \file stockserver.c
 * \brief Concurrent stock server implementation (event-driven approach)
 */

#include "csapp.h"
#include "stock.h"
#include "debug.h"

sem_t global_padlock;

struct stock_item *stock_db;

size_t thread_size;

void echo(int connfd);

void *process_thread(void *vargp);
void process_request(struct stock_item *tree, char *buffer);

void *process_thread(void *vargp)
{
    /* Retrieve the socket descriptor from the argument */
    int connfd = *((int *)vargp);
    free(vargp);

    /* Detach the thread to self-reap */
    Pthread_detach(Pthread_self());

    /* Initialize I/O buffers */
    int buffer_length;
    char buffer[MAXLINE];
    rio_t rio;
    Rio_readinitb(&rio, connfd);

    /* Read requests */
    while ((buffer_length = Rio_readlineb(&rio, buffer, MAXLINE)) != 0)
    {
        /* Process the request */
        process_request(stock_db, buffer);

        /* Echo the request back to the client */
        Rio_writen(connfd, buffer, strlen(buffer));
    }

    debug("closing connection\n");

    /* Close the connection */
    Close(connfd);

    /* Decrement the thread size */
    P(&global_padlock);
    thread_size--;
    V(&global_padlock);

    /* If no thread is connected, update the stock database */
    if (thread_size == 0) {
        debug("updating stock database...\n");
        stock_save(stock_db, "stock.txt");
    }

    return NULL;
}

void process_request(struct stock_item *tree, char *buffer)
{
    debug("processing request: %s", buffer);

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
        P(&global_padlock);
        if (stock_buy(tree, id, amount))
            strcpy(buffer, "[buy] success\n");
        else 
            strcpy(buffer, "[buy] failure\n");
        V(&global_padlock);
    } else if (!strncmp(buffer, "sell ", 5)) {
        /* Sell a stock */

        /* Parse the input */
        int id, amount;
        sscanf(buffer, "sell %d %d\n", &id, &amount);

        /* Try selling the stock */
        P(&global_padlock);
        if (stock_sell(tree, id, amount))
            strcpy(buffer, "[sell] success\n");
        else 
            strcpy(buffer, "[sell] failure\n");
        V(&global_padlock);
    } else if (!strncmp(buffer, "exit\n", 5)) {
        /* Exit from the market */
        
        buffer[0] = '\0';
        return;
    } else {
        /* Invalid command */

        strcpy(buffer, "invalid command\n");
    }

    debug("processed request: %s\n", buffer);
}

int main(int argc, char *argv[])
{
    int listenfd;
    int *connfd_ptr;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    pthread_t tid;

    /* Basic command line argument sanity check */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    /* Initialize debug message facility */
    debug_init();

    /* Initialize the stock database */
    debug("initializing stock database...\n");
    stock_db = stock_init("stock.txt");
    stock_print(stock_db);
    
    /* Open listening file descriptor using the given port */
    debug("opening listening file descriptor...\n");
    listenfd = Open_listenfd(argv[1]);

    /* Initialize the semaphores */
    debug("initializing semaphores...\n");
    Sem_init(&global_padlock, 0, 1);

    /* Main server loop */
    while (1) {
        /* Accept connection from client... */
        debug("waiting for connection...\n");
        clientlen = sizeof(struct sockaddr_storage);
        connfd_ptr = malloc(sizeof(int));
        *connfd_ptr = Accept(listenfd, (SA *)&clientaddr, &clientlen);

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

        /* ...and create request handling thread */
        Pthread_create(&tid, NULL, process_thread, connfd_ptr);
        P(&global_padlock);
        thread_size++;
        debug("created connection thread %zu\n", thread_size);
        V(&global_padlock);
    }

    return 0;
}
