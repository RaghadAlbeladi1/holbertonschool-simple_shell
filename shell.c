#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void handle_eof(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "\n", 1);
}

void shell_loop(void)
{
    char *line = NULL;
    char **args = NULL;
    int status = 1;

    while (status)
    {
        if (isatty(STDIN_FILENO))
            print_prompt();

        line = read_line();
        if (!line)
        {
            handle_eof();
            break;
        }

        args = parse_line(line);
        if (!args)
        {
            free(line);
            line = NULL;
            continue;
        }

        status = execute(args);

        /* Only free if execute() didn't handle it (status != -1) */
        if (status != -1)
        {
            free_args(args);
            free(line);
        }
        args = NULL;
        line = NULL;
    }

    /* Final cleanup */
    if (line) free(line);
    if (args) free_args(args);
}

int main(void)
{
    shell_loop();
    return EXIT_SUCCESS;
}
