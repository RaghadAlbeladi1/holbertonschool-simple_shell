#include "shell.h"

/* Static helper function */
static void handle_eof(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "\n", 1);
}

/* Main shell loop */
void shell_loop(void)
{
    char *line = NULL;  /* Declare variables at block start */
    char **args = NULL;
    int status = 1;

    while (status)
    {
        print_prompt();

        /* Read input */
        line = read_line();
        if (!line)
        {
            handle_eof();  /* Proper C90 comment style */
            break;        /* This is now correctly within the while loop */
        }

        /* Parse and execute */
        args = parse_line(line);
        if (!args)
        {
            free(line);
            continue;
        }

        status = execute(args);

        /* Cleanup */
        free(args);
        free(line);
        args = NULL;
        line = NULL;
    }

    /* Final cleanup */
    if (args)
        free(args);
    if (line)
        free(line);
}
