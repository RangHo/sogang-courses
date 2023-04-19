#include <stdbool.h>
#include <string.h>

#include <errno.h>

#include "csapp.h"

/* Constant definitions *******************************************************/
#define MAXARGS 128
#define HISTFILE ".myshell_p2_history"
#define HISTFILESIZE 128

#define PARSE_RESULT_OK 0
#define PARSE_ERROR_UNMATCHED_QUOTE -1
#define PARSE_ERROR_EXPECTED_EOL -2

/* Utility macro definitions **************************************************/
#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

/* Data structures ************************************************************/
struct node {
    enum {
        NODE_TYPE_EMPTY,
        NODE_TYPE_COMMAND,
        NODE_TYPE_PIPE,
    } type;
    union {
        struct {
            int argc;
            char* argv[MAXLINE];
            bool background;
        } command;
        struct {
            struct node* left;
            struct node* right;
        } pipe;
    } data;
};

/* Function prototypes ********************************************************/

/* Main evaluation helpers */
void eval(char* cmdline);
void eval_node(struct node* node);
int parse(char* buf, struct node** prog);

/* Command parsing helpers */
struct node* node_new();
void node_delete(struct node* node);
void node_debug(struct node* node);
void node_string(struct node* node, char* buf);

/* Built-in command handlers */
int builtin_quit(char* argv[]);
int builtin_command(char* argv[]);
int builtin_cd(char* argv[]);
int builtin_history(char* argv[]);

/* History helpers */
void history_init();
void history_add(struct node* node);
void history_at(int index, char* buf);
void history_last(char* buf);

/* Predicates */
bool is_whitespace(char c);
bool is_quotation(char c);

/* Signal handlers ************************************************************/
void handle_sigchld(int sig);
void handle_sigterm(int sig);

/* Global variables ***********************************************************/
bool exit_flag = false;
bool history_enabled = true;
bool history_replaced = false;

/* Function implementations ***************************************************/

/* $begin shellmain */
/* Entrypoint */
int main(void)
{
    /* Command line buffer */
    char cmdline[MAXLINE];

    /* Install signal handlers */
    signal(SIGCHLD, handle_sigchld);
    signal(SIGTERM, handle_sigterm);

    /* Initialize history */
    history_init();

    /* REPL */
    while (1) {
        /* Read */
        printf("CSE4100-MP-P1 > ");
        fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
            exit(0);

        /* Evaluate */
        eval(cmdline);
    }
}
/* $end shellmain */

/* $begin eval */
/* eval - Evaluate a command line */
void eval(char* cmdline)
{
    char* argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int parse_result;    /* Result of parse() */
    pid_t pid;           /* Process id */

    strcpy(buf, cmdline);
    debug("eval: Content of buf: %s", buf);

    struct node* prog;
    parse_result = parse(buf, &prog);

    /* Add the command to history*/
    history_add(prog);

#ifdef DEBUG
    node_debug(prog);
#endif

    if ((pid = fork()) == 0)
        eval_node(prog);

    int status;
    if (waitpid(pid, &status, 0) < 0)
        unix_error("eval: waitpid error");

    node_delete(prog);
}

/* eval_node - Evaluate a node */
void eval_node(struct node* node)
{
    int status;
    pid_t pid_left, pid_right;
    switch (node->type) {
    case NODE_TYPE_EMPTY:
        /* Do nothing */
        debug("eval_node: Empty node.\n");
        break;

    case NODE_TYPE_COMMAND:
        /* Run the command */
        debug("eval_node: Command node.\n");

        /* If the command is a built-in one, run that */
        if (builtin_command(node->data.command.argv))
            return;

        /* Otherwise, run the command */
        execvp(node->data.command.argv[0], node->data.command.argv);

        printf("%s: Command not found.\n", node->data.command.argv[0]);
        break;

    case NODE_TYPE_PIPE:
        /* Create a pipe and run the child nodes */
        debug("eval_node: Pipe node.\n");

        /* Create a pipe */
        int pipefd[2];
        if (pipe(pipefd) < 0)
            unix_error("eval_node: pipe error");

        debug("eval_node: Read end: %d.\n", pipefd[0]);
        debug("eval_node: Write end: %d.\n", pipefd[1]);

        /* Fork the "left" process */
        if ((pid_left = fork()) == 0) {
            /* This is inside the child process */
            /* We don't need the read end at all */
            close(pipefd[0]);

            /* Replace stdout with the write end of the pipe */
            dup2(pipefd[1], STDOUT_FILENO);

            /* Now the write end is no longer needed */
            close(pipefd[1]);

            /* Run the command node */
            eval_node(node->data.pipe.left);
        }

        /* Fork the "right" process */
        if ((pid_right = fork()) == 0) {
            /* This is inside the child process */
            /* We don't need the write end at all */
            close(pipefd[1]);

            /* Replace stdin with the read end of the pipe */
            dup2(pipefd[0], STDIN_FILENO);

            /* Now the read end is no longer needed */
            close(pipefd[0]);

            /* Run the rest node */
            eval_node(node->data.pipe.right);
        }

        /* Close the pipe */
        close(pipefd[0]);
        close(pipefd[1]);

        /* Wait for the child processes to terminate */
        waitpid(pid_left, &status, 0);
        waitpid(pid_right, &status, 0);

        break;

    default:
        /* This code path should never be reached */
        printf("eval_node: Unknown node type: %d\n", node->type);
        break;
    }

    exit(0);
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char* argv[])
{
    debug("builtin_command: Checking if %s is a built-in command...\n", argv[0]);

    /* `quit` or `exit` command */
    if (!strcmp(argv[0], "quit") || !strcmp(argv[0], "exit"))
        return builtin_quit(argv);

    /* `cd` command */
    if (!strcmp(argv[0], "cd"))
        return builtin_cd(argv);

    /* `history` command */
    if (!strcmp(argv[0], "history"))
        return builtin_history(argv);

    /* Ignore singleton `&` */
    if (!strcmp(argv[0], "&"))
        return 1;

    /* Not a built-in command */
    debug("builtin_command: %s is not a built-in command.\n", argv[0]);
    return 0;
}

/* Built-in `quit` command handler */
int builtin_quit(char* _[])
{
    debug("builtin_quit: Quitting.\n");

    /* Get the parent PID */
    pid_t parent_pid = getppid();

    /* Kill the parent with SIGKILL */
    kill(parent_pid, SIGTERM);

    /* Self destruct */
    exit(0);

    /* This function never returns */
    return 1;
}

/* Built-in `cd` command handler */
int builtin_cd(char* argv[])
{
    debug("builtin_cd: Changing directory to \"%s\"...\n", argv[1] != NULL ? argv[1] : "~");

    /* If no argument is given, go to home directory */
    if (argv[1] == NULL)
        chdir(getenv("HOME"));
    else
        chdir(argv[1]);
    return 1;
}

/* Built-in `history` command handler */
int builtin_history(char* _[])
{
    debug("builtin_history: Displaying history...\n");

    /* Open history file */
    char histfile_path[MAXLINE];
    sprintf(histfile_path, "%s/%s", getenv("HOME"), HISTFILE);
    FILE* fp = fopen(histfile_path, "r");
    if (fp == NULL) {
        printf("builtin_history: Cannot open history file.\n");
        return 1;
    }

    /* Read history file line by line */
    char buf[MAXLINE];
    int index = 1;
    while (fgets(buf, MAXLINE, fp) != NULL) {
        /* Remove trailing newline */
        buf[strlen(buf) - 1] = '\0';

        /* Print history entry */
        printf("%3d %s\n", index, buf);
        index++;
    }

    /* Close history file */
    fclose(fp);

    return 1;
}
/* $end eval */

/* $begin parse */
/* parse - Parse the command line and build the argv array */
int parse(char* buf, struct node** prog)
{
    /* Temporary buffer to do string manipulations */
    static char temp_buf[MAXLINE];

    /* Result node */
    struct node* result = node_new();
    result->type = NODE_TYPE_COMMAND;
    result->data.command.argc = 0;
    result->data.command.argv[0] = NULL;
    result->data.command.background = false;

    /* Ignore leading spaces */
    while (*buf && is_whitespace(*buf))
        buf++;

    /* Replace the trailing newline with a space */
    buf[strlen(buf) - 1] = ' ';

    debug("parse: Trimmed command: %s\n", buf);

    /* Parse the command line */
    int argc = 0;
    char* word = NULL;
    char quote = '\0';
    struct node** target = &result;
    history_replaced = false;
    while (1) {
        /* Show current state */
        debug("parse: Current state: %x %x %d\n", buf, word, quote);

        /* Cases to consider:
           1. If the current character is a quotation and quote is NUL,
           then it is a beginning of a quoted string.
           2. If the current character is a quotation and quote is not NUL,
           then it is an ending of a quoted string.
           3. If the current character is not a whitespace and word is NULL,
           then we are at the beginning of a word.
           4. If the current character is a whitespace and word is not NULL,
           then we are at the end of a word.
           5. If the current character is a whitespace and word is NULL,
           ignore and process the next character.
           6. If the current character is not a whitespace and word is not NULL
           ignore and process the next character.
           7. If the current character is an ampersand, wrap up everything and
           expect an EOL.
           8. If the current character is a pipe, wrap up the current command
           and setup a new command target to parse
           9. If the current character is EOL, wrap up. */

        if (*buf == '\0') {
            /* EOL */
            debug("parse: End of line.\n");

            /* If we are in a quoted string, it is an error */
            if (quote != '\0') {
                printf("parse: Unmatched quote.\n");
                return PARSE_ERROR_UNMATCHED_QUOTE;
            }

            /* Make sure that the argv ends with NULL */
            (*target)->data.command.argv[argc] = NULL;

            /* Set the argument count */
            (*target)->data.command.argc = argc;

            /* We are done */
            break;
        } else if (*buf == '&' && quote == '\0') {
            /* ampersand */
            debug("parse: Background job indicator.\n");

            /* If we are in the middle of a word, wrap it up */
            if (word != NULL) {
                *buf = '\0';
                (*target)->data.command.argv[argc++] = word;
                debug("The word is '%s'.\n", word);
                word = NULL;
            }

            /* Make sure that the argv ends with NULL */
            (*target)->data.command.argv[argc] = NULL;

            /* Set the argument count */
            (*target)->data.command.argc = argc;

            /* Set the background flag */
            (*target)->data.command.background = true;

            /* Skip the ampersand */
            buf++;

            /* Skip the trailing spaces */
            while (*buf && is_whitespace(*buf))
                buf++;

            /* Make sure that the next character is EOL */
            if (*buf != '\0') {
                printf("parse: Unexpected character '%c' after '&'.\n", *buf);
                return PARSE_ERROR_EXPECTED_EOL;
            }

            /* We are done */
            break;
        } else if (*buf == '|' && quote == '\0') {
            /* pipe */
            debug("parse: Pipe found.\n");

            /* If we are in the middle of a word, wrap it up */
            if (word != NULL) {
                *buf = '\0';
                (*target)->data.command.argv[argc++] = word;
                debug("The word is '%s'.\n", word);
                word = NULL;
            }

            /* Make sure that the argv ends with NULL */
            (*target)->data.command.argv[argc] = NULL;

            /* Set the argument count */
            (*target)->data.command.argc = argc;

            /* Create a new pipe container node */
            struct node* pipe = node_new();
            pipe->type = NODE_TYPE_PIPE;

            /* The current target node becomes the "left" of pipe */
            pipe->data.pipe.left = *target;

            /* The new target node becomes the "right" of pipe */
            pipe->data.pipe.right = node_new();
            pipe->data.pipe.right->type = NODE_TYPE_COMMAND;
            pipe->data.pipe.right->data.command.background = false;

            /* Update the target node */
            *target = pipe;

            /* Set the new target node */
            target = &pipe->data.pipe.right;

            /* Reset the argument count */
            argc = 0;
        } else if (*buf == '!' && quote == '\0') {
            /* bang -> history related replacements */
            debug("parse: Bang found.\n");

            /* Is this !!? */
            if (strncmp(buf, "!!", 2) == 0) {
                /* Get the last command from history into temporary buffer */
                history_last(temp_buf);

                /* Replace trailing newline with NUL */
                temp_buf[strlen(temp_buf) - 1] = '\0';

                /* Concatenate the rest into the temporary buffer */
                strcat(temp_buf, buf + 2);

                /* Copy the temporary buffer back to the original buffer */
                strcpy(buf, temp_buf);

                /* Reset the temporary buffer */
                temp_buf[0] = '\0';

                /* Try this buffer again */
                continue;
            }

            /* Is this !N? */
            int i = 0;
            while (isdigit(buf[i + 1]))
                i++;

            if (i > 0) {
                /* History replacement occured here */
                history_replaced = true;

                /* Get the Nth command from history into temporary buffer */
                history_at(atoi(buf + 1), temp_buf);

                /* Replace trailing newline with NUL */
                temp_buf[strlen(temp_buf) - 1] = '\0';

                /* Concatenate the rest into the temporary buffer */
                strcat(temp_buf, buf + i + 1);

                /* Copy the temporary buffer back to the original buffer */
                strcpy(buf, temp_buf);

                /* Reset the temporary buffer */
                temp_buf[0] = '\0';

                /* Try this buffer again */
                continue;
            }
        } else if (is_quotation(*buf) && quote == '\0') {
            /* 1. quotation and quote is NUL */
            debug("parse: Beginning of a quoted string starting with '%c'.\n", *buf);
            quote = *buf++;
            word = buf;
        } else if (is_quotation(*buf) && *buf == quote) {
            /* 2. quotation and quote is not NUL */
            debug("parse: End of a quoted string.\n");
            *buf = '\0';
            (*target)->data.command.argv[argc++] = word;
            debug("The word is '%s'.\n", word);
            word = NULL;
            quote = '\0';
        } else if (!is_quotation(*buf) && quote != '\0') {
            /* 3. not in a quotation and quote is not NUL */
            debug("parse: In a quoted string.\n");
        } else if (!is_whitespace(*buf) && word == NULL) {
            /* 3. not whitespace and word is NULL */
            debug("parse: Beginning of a word starting with '%c'.\n", *buf);
            word = buf;
        } else if (is_whitespace(*buf) && word != NULL) {
            /* 4. whitespace and word is not NULL */
            debug("parse: End of a word.\n");
            *buf = '\0';
            (*target)->data.command.argv[argc++] = word;
            debug("The word is '%s'.\n", word);
            word = NULL;
        } else if (is_whitespace(*buf) && word == NULL) {
            /* 5. whitespace and word is NULL */
            debug("parse: Ignoring whitespace.\n");
        } else if (!is_whitespace(*buf) && word != NULL) {
            /* 6. not whitespace and word is not NULL */
            debug("parse: Ignoring character '%c'.\n", *buf);
        } else {
            /* This code path should never be reached */
            printf("parse: Unknown case: %c %c %c\n", *buf, *word, quote);
        }

        /* Increment buffer pointer */
        buf++;
    }

    /* If the result is a command node and argc is still 0, convert it to a
       NODE_TYPE_EMPTY node */
    if (result->type == NODE_TYPE_COMMAND && result->data.command.argc == 0)
        result->type = NODE_TYPE_EMPTY;

    /* Set the result */
    *prog = result;

    return PARSE_RESULT_OK;
}

/* node_new - Create a new node */
struct node* node_new()
{
    struct node* node = malloc(sizeof(struct node));
    return node;
}

/* node_delete - Delete a node */
void node_delete(struct node* node)
{
    /* In case of a pipe node, recursively delete the nodes */
    if (node->type == NODE_TYPE_PIPE) {
        node_delete(node->data.pipe.left);
        node_delete(node->data.pipe.right);
    }

    /* Now self-destruct */
    free(node);
}

/* node_debug - Print a node, if debugging is enabled */
void node_debug(struct node* node)
{
    if (node->type == NODE_TYPE_COMMAND) {
        debug(
            "node_debug: %s command node: %s\n",
            node->data.command.background ? "Background" : "Foreground",
            node->data.command.argv[0]
        );
        debug("node_debug: It has %d arguments: ", node->data.command.argc);
        for (int i = 0; i < node->data.command.argc; i++) {
            debug("%s ", node->data.command.argv[i]);
        }
        debug("\n");
    } else if (node->type == NODE_TYPE_PIPE) {
        debug("node_debug: Pipe node:\n");
        debug("node_debug: Left:\n");
        node_debug(node->data.pipe.left);
        debug("node_debug: Right:\n");
        node_debug(node->data.pipe.right);
    }
}

/* node_string - Return a string representation of a node */
void node_string(struct node* node, char* buf)
{
    /* Reset the buffer first */
    buf[0] = '\0';

    switch (node->type) {
    case NODE_TYPE_EMPTY:
        strcpy(buf, " ");
        break;

    case NODE_TYPE_COMMAND:
        for (int i = 0; i < node->data.command.argc; i++) {
            strcat(buf, node->data.command.argv[i]);
            strcat(buf, " ");
        }
        break;

    case NODE_TYPE_PIPE:
        node_string(node->data.pipe.left, buf);
        strcat(buf, "| ");
        node_string(node->data.pipe.right, buf + strlen(buf));
        break;
    }
}

/* is_whatespace - Check if the character is a whitespace character */
bool is_whitespace(char c) { return c == ' ' || c == '\t'; }

/* is_quotation - Check if the character is a quotation character */
bool is_quotation(char c) { return c == '\'' || c == '"' || c == '`'; }
/* $end parse */

/* $begin handlers */
/* handle_sigchld - SIGCHLD signal handler */
void handle_sigchld(int _)
{
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        debug("handle_sigchld: Child process %d terminated.\n", pid);
    }
}

/* handle_sigterm - SIGTERM signal handler */
void handle_sigterm(int _)
{
    /* Graceful quit request received, so quit */
    exit(0);
}
/* $end handlers */

/* $begin history */
/* history_init - Initialize the history file */
void history_init()
{
    /* Assemble the history file path */
    char histfile_path[MAXLINE];
    sprintf(histfile_path, "%s/%s", getenv("HOME"), HISTFILE);

    /* Check if the file exists, and if it does, do nothing */
    if (access(histfile_path, R_OK | W_OK) == 0) {
        debug("history_init: History file already exists.\n");
        return;
    }

    /* Create the history file */
    debug("history_init: Creating history file...\n");
    FILE* fp = fopen(histfile_path, "w");
    if (fp == NULL) {
        unix_error("history_init: Failed to create history file");
    }

    /* Close the file */
    fclose(fp);
}

/* history_add - Add a command to the history file */
void history_add(struct node* node)
{
    /* Buffer to save the stringified node */
    static char buf[MAXLINE];
    node_string(node, buf);

    /* If history replacement happened, print the command first */
    if (history_replaced)
        printf("%s\n", buf);

    /* Open the history file */
    debug("history_add: Opening history file...\n");
    char histfile_path[MAXLINE];
    sprintf(histfile_path, "%s/%s", getenv("HOME"), HISTFILE);

    FILE* fp = fopen(histfile_path, "a");
    if (fp == NULL) {
        unix_error("history_add: Failed to open history file");
    }

    /* If the last command is the same as the current one, do nothing */
    char lastcmd[MAXLINE];
    history_last(lastcmd);

    /* Remove the trailing newline */
    lastcmd[strlen(lastcmd) - 1] = '\0';

    debug("history_add: Last command: %s\n", lastcmd);
    debug("history_add: Current command: %s\n", buf);
    if (strcmp(lastcmd, buf) == 0) {
        debug("history_add: The last command is the same as the current one.\n");
        goto cleanup;
    }

    /* Write the command to the history file */
    debug("history_add: Writing command to history file...\n");
    fprintf(fp, "%s\n", buf);

cleanup:
    /* Close the file */
    fclose(fp);
}

/* history_at - Get the command at the specified index */
void history_at(int index, char* buf)
{
    /* Open the history file */
    debug("history_at: Opening history file...\n");
    char histfile_path[MAXLINE];
    sprintf(histfile_path, "%s/%s", getenv("HOME"), HISTFILE);

    FILE* fp = fopen(histfile_path, "r");
    if (fp == NULL) {
        unix_error("history_at: Failed to open history file");
    }

    /* Read the command at the specified index */
    debug("history_at: Reading command at index %d...\n", index);
    for (int i = 0; i < index; i++)
        if (fgets(buf, MAXLINE, fp) == NULL)
            unix_error("history_at: Failed to read command at index");

    /* Close the file */
    fclose(fp);
}

/* history_last - Get the last command in the history file */
void history_last(char* buf)
{
    /* Open the history file */
    debug("history_last: Opening history file...\n");
    char histfile_path[MAXLINE];
    sprintf(histfile_path, "%s/%s", getenv("HOME"), HISTFILE);

    FILE* fp = fopen(histfile_path, "r");
    if (fp == NULL) {
        unix_error("history_last: Failed to open history file");
    }

    /* Read the last command in the history file */
    debug("history_last: Reading last command...\n");
    while (fgets(buf, MAXLINE, fp) != NULL)
        /* Do nothing */;

    /* Close the file */
    fclose(fp);
}
/* $end history */
