#include "shell.h"

/**
 * execute_command - Executes a command using fork and exec
 * @command: The command to execute
 *
 * Return: Exit status of the command
 */
int execute_command(const char *command)
{
    pid_t pid;
    int status;
    char *args[MAX_ARGS];
    char *token;
    int i = 0;
    char *cmd_copy = strdup(command);

    if (!cmd_copy)
        return (-1);

    token = strtok(cmd_copy, " ");
    while (token && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid = fork();
    if (pid == -1)
    {
        print_message("Error forking process.\n");
        free(cmd_copy);
        return (-1);
    }

    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            print_message(args[0]);
            print_message(": command not found\n");
            free(cmd_copy);
            exit(127);
        }
    }

    waitpid(pid, &status, 0);
    free(cmd_copy);

    if (WIFEXITED(status))
        return (WEXITSTATUS(status));

    return (-1);
}
