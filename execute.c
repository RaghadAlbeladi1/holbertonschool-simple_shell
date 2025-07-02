#include "shell.h"

/**
 * execute - Execute a command
 * @args: Array of arguments
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args)
{
    pid_t pid;
    int status;

    if (args[0] == NULL)
        return 1;

    /* Handle built-in commands */
    if (handle_builtins(args))
        return -1;

    /* Execute external command */
    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("hsh");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("hsh");
    }
    else
    {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
