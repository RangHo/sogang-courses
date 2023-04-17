#include <stdbool.h>

#include <errno.h>

#include "csapp.h"

/* Constant definitions *******************************************************/
#define MAXARGS 128
#define HISTFILE ".myshell_history"
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
int parse(char* buf, struct node** prog);

/* Command parsing helpers */
struct node* node_new();
void node_delete(struct node* node);
void node_debug(struct node* node);

/* Built-in command handlers */
int builtin_quit(char* argv[]);
int builtin_command(char* argv[]);
int builtin_cd(char* argv[]);
int builtin_history(char* argv[]);
int builtin_history_replay(char* argv[]);
int builtin_history_at(char* argv[]);

/* History helpers */
void history_init();
void history_add(char* cmdline);
void history_at(int index, char* buf);
void history_last(char* buf);

/* Predicates */
bool is_whitespace(char c);
bool is_quotation(char c);


/* Signal handlers ************************************************************/
void handle_sigchld(int sig);


/* Global variables ***********************************************************/
bool history_enabled = true;


/* Function implementations ***************************************************/

/* $begin shellmain */
/* Entrypoint */
int main(void)
{
    /* Command line buffer */
    char cmdline[MAXLINE];

    /* Install signal handlers */
    Signal(SIGCHLD, handle_sigchld);

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
    char* argv[MAXARGS];   /* Argument list execve() */
    char buf[MAXLINE];     /* Holds modified command line */
    int parse_result;      /* Result of parse() */
    pid_t pid;             /* Process id */

    strcpy(buf, cmdline);
    debug("eval: Content of buf: %s", buf);

    struct node* prog;
    parse_result = parse(buf, &prog);

#ifdef DEBUG
    node_debug(prog);
    node_delete(prog);
    return;
#endif

    /* Ignore empty lines */
    if (argv[0] == NULL)
        return;

    /* Add the command to history if they don't start with a bang */
    if (history_enabled && argv[0][0] != '!')
        history_add(cmdline);

    /* If the command is a built-in one, run that */
    if (builtin_command(argv))
        return;

    /* Otherwise, fork a child process and run the command */
    if ((pid = fork()) == 0) {
        /* This is inside the child process */
        if (execvp(argv[0], argv) < 0) {
            printf("%s: Command not found.\n", argv[0]);
            exit(0);
        }

        /* This code path should never be reached */
    }

    int status;
    switch (parse_result) {
    case PARSE_RESULT_OK:
        /* Wait for the child process to terminate */
        if (waitpid(pid, &status, 0) < 0)
            unix_error("eval: Waitpid error");
        /* Do not wait for the child process to terminate */
        printf("%d %s", pid, cmdline);
        break;

    default:
        /* This code path should never be reached */
        printf("eval: Unknown parse result: %d\n", parse_result);
        break;
    }
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char* argv[])
{
    debug(
          "builtin_command: Checking if %s is a built-in command...\n", argv[0]);

    /* `quit` or `exit` command */
    if (!strcmp(argv[0], "quit") || !strcmp(argv[0], "exit"))
        return builtin_quit(argv);

    /* `cd` command */
    if (!strcmp(argv[0], "cd"))
        return builtin_cd(argv);

    /* `history` command */
    if (!strcmp(argv[0], "history"))
        return builtin_history(argv);

    /* `!!` command */
    if (!strcmp(argv[0], "!!"))
        return builtin_history_replay(argv);
    
    /* `!N` command */
    if (argv[0][0] == '!')
        return builtin_history_at(argv);

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

    exit(0);

    /* This function never returns */
    return 1;
}

/* Built-in `cd` command handler */
int builtin_cd(char* argv[])
{
    debug("builtin_cd: Changing directory to \"%s\"...\n",
          argv[1] != NULL ? argv[1] : "~");

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

/* Built-in `!!` command handler */
int builtin_history_replay(char* _[])
{
    debug("builtin_history_replay: Replaying last command...\n");

    /* Command line buffer */
    char cmdline[MAXLINE];

    /* Get the last command from history */
    history_last(cmdline);

    /* Disable history for now */
    history_enabled = false;

    /* Evaluate the command */
    eval(cmdline);

    /* Re-enable history */
    history_enabled = true;

    return 1;
}

/* Built-in `!N` command handler */
int builtin_history_at(char* argv[])
{
    int index = atoi(argv[0] + 1);
    debug("builtin_history_at: Replaying command at index %d...\n", index);

    /* Command line buffer */
    char cmdline[MAXLINE];

    /* Get the command at the given index from history */
    history_at(index, cmdline);

    /* Evaluate the command */
    eval(cmdline);

    return 1;
}
/* $end eval */

/* $begin parse */
/* parse - Parse the command line and build the argv array */
int parse(char* buf, struct node** prog)
{
    /* Result node */
    struct node* result = node_new();
    result->type = NODE_TYPE_COMMAND;
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
    while (1) {
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
        } else if (is_quotation(*buf) && quote == '\0') {
            /* 1. quotation and quote is NUL */
            debug("parse: Beginning of a quoted string starting with '%c'.\n",
                  *buf);
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

        /* Show current state */
        debug("parse: Current state: %x %x %d\n", buf, word, quote);
        
        /* Increment buffer pointer */
        buf++;
    }

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
            node->data.command.background
                ? "Background"
                : "Foreground",
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

/* is_whatespace - Check if the character is a whitespace character */
bool is_whitespace(char c)
{
    return c == ' ' || c == '\t';
}

/* is_quotation - Check if the character is a quotation character */
bool is_quotation(char c)
{
    return c == '\'' || c == '"' || c == '`';
}
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
void history_add(char* cmdline)
{
    /* Open the history file */
    debug("history_add: Opening history file...\n");
    char histfile_path[MAXLINE];
    sprintf(histfile_path, "%s/%s", getenv("HOME"), HISTFILE);
    
    FILE* fp = fopen(histfile_path, "a");
    if (fp == NULL) {
        unix_error("history_add: Failed to open history file");
    }

    /* Write the command to the history file */
    debug("history_add: Writing command to history file...\n");
    fprintf(fp, "%s", cmdline);

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
