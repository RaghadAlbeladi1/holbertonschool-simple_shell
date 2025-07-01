#include "shell.h"

/**
 * main - Entry point
 * Return: Always 0
 */
int main(void)
{
    shell_loop();
    return EXIT_SUCCESS;
}

/**
 * shell_loop - Main shell loop
 */
void shell_loop(void)
{
    char *line;
    char **args;
    int status = 1;

    while (status)
    {
        print_prompt();
        line = read_line();
        if (!line)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        args = parse_line(line);
        if (args)
        {
            status = execute(args);
            free(args);
        }
        free(line);
    }
}
