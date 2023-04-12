/* $begin shellmain */
#include <errno.h>

#include "csapp.h"

/* Constant definitions */
#define MAXARGS 128
#define HISTFILE ".myshell_history"
#define HISTFILESIZE 128

/* Utility macro definitions */
#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

/* Function prototypes */
void eval(char* cmdline);
int parse(char* buf, char* argv[]);
int builtin_quit(char* argv[]);
int builtin_command(char* argv[]);
int builtin_cd(char* argv[]);
int builtin_history(char* argv[]);

void add_history(char* cmdline);
void read_history(unsigned int index);

/* Signal handlers */
void handle_sigchld(int sig);

int main()
{
    char cmdline[MAXLINE]; /* Command line */

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
    int bg;                /* Should the job run in bg or fg? */
    pid_t pid;             /* Process id */

    strcpy(buf, cmdline);
    debug("eval: Content of buf: %s\n", buf);

    bg = parse(buf, argv);
    debug("eval: Is background job? %d\n", bg);

    /* Ignore empty lines */
    if (argv[0] == NULL)
        return;

    /* If the command is a built-in one, run that */
    if (!builtin_command(argv)) {
        /* Fork and exec */
        if ((pid = Fork()) == 0) {
            /* Inside child process */
            if (execvp(argv[0], argv) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        /* Parent waits for foreground job to terminate */
        if (!bg) {
            /* Wait for the child process to terminate */
            int status;
            if (Waitpid(pid, &status, 0) < 0)
                unix_error("waitfg: waitpid error");
        } else {
            printf("%d %s", pid, cmdline);
            Signal(SIGCHLD, handle_sigchld);
        }
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char* argv[])
{
    debug(
        "builtin_command: Checking if %s is a built-in command...\n", argv[0]);

    /* `quit` command */
    if (!strcmp(argv[0], "quit"))
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
int builtin_quit(char* _argv[])
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
int builtin_history(char* _args[])
{
    debug("builtin_history: Displaying history...\n");

    FILE* fp;

    char histfile_path[MAXLINE];

    /* Assemble the path to the history file */
    sprintf(histfile_path, "%s/%s", getenv("HOME"), HISTFILE);

    /* Try opening history file */
    if ((fp = fopen(histfile_path, "r")) == NULL) {
        /* If the file doesn't exist, create it */
        debug("builtin_history: Failed to open history file. Creating...\n");
        fclose(fopen(histfile_path, "w"));

        /* Open history file again */
        fp = fopen(histfile_path, "r");
    }

    /* Read history file */
    char line[MAXLINE];
    int i = 0;
    while (fgets(line, MAXLINE, fp) != NULL) {
        printf("%3d %s", i, line);
        i++;
    }

    return 1;
}
/* $end eval */

/* $begin parse */
/* parse - Parse the command line and build the argv array */
int parse(char* buf, char* argv[])
{
    char* delim; /* Points to first space delimiter */
    int argc;    /* Number of args */
    int bg;      /* Background job? */

    buf[strlen(buf) - 1] = ' ';   /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
        buf++;

    debug("parse: Trimmed command: %s\n", buf);

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;

        debug("parse: argv[%d] = %s\n", argc - 1, argv[argc - 1]);

        /* Ignore spaces */
        while (*buf && (*buf == ' '))
            buf++;
    }
    argv[argc] = NULL;

    if (argc == 0) /* Ignore blank line */
        return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc - 1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}
/* $end parse */

/* $begin handlers */
/* handle_sigchld - SIGCHLD signal handler */
void handle_sigchld(int _sig)
{
    pid_t pid;
    while ((pid = Wait(NULL)) > 0)
        /* do nothing */;
}
/* $end handlers */
