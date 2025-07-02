#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* Helper function to handle EOF (Ctrl+D) */
static void handle_eof(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "\n", 1);
}

/* Main shell loop */
void shell_loop(void)
{
    char *line = NULL;      /* Buffer for user input */
    char **args = NULL;     /* Array of command arguments */
    int status = 1;         /* Loop control flag */

    while (status)
    {
        /* Display prompt in interactive mode */
        if (isatty(STDIN_FILENO))
            print_prompt();

        /* Read user input */
        line = read_line();
        if (!line)
        {
            handle_eof();
            break;
        }

        /* Parse input into arguments */
        args = parse_line(line);
        if (!args)
        {
            free(line);
            line = NULL;
            continue;
        }

        /* Execute the command */
        status = execute(args);

        /* Free memory (only if not already freed by builtins) */
        if (status != -1)
        {
            free_args(args);
            free(line);
        }
        args = NULL;
        line = NULL;
    }

    /* Additional cleanup as safety measure */
    if (line)
    {
        free(line);
        line = NULL;
    }
    if (args)
    {
        free_args(args);
        args = NULL;
    }
}

/* Program entry point */
int main(void)
{
    shell_loop();
    
    /* 
     * No need to free environ here as it's
     * maintained by the system
     */
    return EXIT_SUCCESS;
}
