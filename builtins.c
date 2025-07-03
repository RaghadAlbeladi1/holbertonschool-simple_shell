#include "shell.h"

/**
 * handle_builtin - Handles built-in shell commands
 * @command: The command to check
 *
 * Return: 1 if builtin handled, -1 if exit, 0 otherwise
 */
int handle_builtin(char *command)
{
    char *cmd = strtok(command, " ");
    int i = 0;
    extern char **environ;

    if (!cmd)
        return (0);

    if (strcmp(cmd, "exit") == 0)
        return (-1);

    if (strcmp(cmd, "env") == 0)
    {
        while (environ[i])
        {
            print_message(environ[i]);
            print_message("\n");
            i++;
        }
        return (1);
    }

    return (0);
}
