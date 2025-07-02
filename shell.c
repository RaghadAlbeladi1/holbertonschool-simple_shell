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
            continue;
        }

        status = execute(args);

        free_args(args);
        free(line);
    }
}

/* Entry point */
int main(void)
{
    shell_loop();
    return 0;
}
