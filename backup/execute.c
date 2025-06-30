#include "shell.h"

/**
 * execute - Executes command with args
 * @args: Null-terminated argument array
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args)
{
    if (args[0] == NULL)
        return (1);

    if (strcmp(args[0], "exit") == 0)
        return (shell_exit(args));
    if (strcmp(args[0], "env") == 0)
        return (shell_env(args));

    return (launch(args));
}

/**
 * launch - Launches external programs
 * @args: Null-terminated argument array
 * Return: 1 to continue
 */
int launch(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("Error");
    }
    else
    {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return (1);
}

/* Built-in functions */
int shell_exit(char **args)
{
    (void)args;
    return (0);
}

int shell_env(char **args)
{
    (void)args;
    for (char **env = environ; *env; env++)
        printf("%s\n", *env);
    return (1);
}
