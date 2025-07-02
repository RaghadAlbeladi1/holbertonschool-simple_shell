#include "shell.h"

/**
 * main - Entry point for simple shell
 * Return: EXIT_SUCCESS on normal exit
 */
int main(void)
{
    shell_loop();
    return EXIT_SUCCESS;
}

/**
 * shell_loop - Main shell REPL (Read-Eval-Print Loop)
 * 
 * Description: Handles the main shell loop with proper memory management
 */
void shell_loop(void)
{
    char *line = NULL;
    char **args = NULL;
    int status = 1;

    while (status)
    {
        print_prompt();

        /* Read */
        line = read_line();
        if (!line)
        {
            handle_eof();
            break;
        }

        /* Evaluate */
        args = parse_line(line);
        if (!args)
        {
            free(line);
            continue;
        }

        /* Execute */
        status = execute(args);

        /* Cleanup */
        free(args);
        free(line);
        args = NULL;
        line = NULL;
    }

    /* Final cleanup (redundant but safe) */
    if (args) free(args);
    if (line) free(line);
}

/**
 * handle_eof - Handles End-of-File condition
 * 
 * Description: Prints newline only if in interactive mode
 */
static void handle_eof(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "\n", 1);
}
