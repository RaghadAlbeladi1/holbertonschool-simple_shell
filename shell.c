#include "shell.h"

/**
 * main - Main shell loop
 *
 * Return: 0 on success, or exits with last command status on exit command
 */
int main(void)
{
    char command[120];
    int last_status = 0;
    int builtin_status;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            display_prompt();

        read_command(command, sizeof(command));

        if (command[0] == '\0')
            continue;

        builtin_status = handle_builtin(command);
        if (builtin_status == -1)
            exit(last_status);

        if (builtin_status == 1)
            continue;

        last_status = execute_command(command);
    }

    return (last_status);
}
