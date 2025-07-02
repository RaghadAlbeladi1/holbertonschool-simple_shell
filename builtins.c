#include "shell.h"

/**
 * handle_builtin - Check and execute built-in commands
 * @command: Input command string
 *
 * Return: -1 if exit was called, 1 if builtin was handled, 0 otherwise
 */
int handle_builtin(char *command)
{
    char *cmd = strtok(command, " ");
    char *arg = strtok(NULL, " ");

    if (strcmp(cmd, "exit") == 0)
    {
        if (arg == NULL)
        {

            return (-1);
        }
        else
        {

            int status = atoi(arg);
            exit(status);
        }
    }
    else if (strcmp(cmd, "env") == 0)
    {
        extern char **environ;
        int i = 0;

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
