#include "shell.h"

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always 0 (success), or exits with last command status
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    int last_status = 0;
    int builtin_status;

    while (1)
    {
        /* Display prompt if in interactive mode */
        if (isatty(STDIN_FILENO))
            display_prompt();

        /* Read user input */
        if (read_command(command, sizeof(command))
        {
            last_status = 1;
            continue;
        }

        /* Skip empty commands */
        if (command[0] == '\0')
            continue;

        /* Handle built-in commands */
        builtin_status = handle_builtin(command);
        if (builtin_status == -1)  /* Exit command */
            exit(last_status);
        if (builtin_status == 1)   /* Handled builtin (e.g., env) */
            continue;

        /* Execute external command */
        last_status = execute_command(command);
    }

    return (0);
}
