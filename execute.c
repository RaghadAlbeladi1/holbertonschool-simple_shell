#include "shell.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * execute - Executes a command with arguments
 * @args: Array of command and arguments
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args)
{
    pid_t pid;
    int status;
    struct stat st;

    if (args[0] == NULL)
        return (1); /* Empty command */

    /* Handle built-in commands */
    if (_strcmp(args[0], "exit") == 0)
        return (0);

    if (_strcmp(args[0], "env") == 0)
    {
        char **env = environ;
        while (*env)
            printf("%s\n", *env++);
        return (1);
    }

    /* Check if command exists */
    if (stat(args[0], &st) == -1)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        return (1);
    }

    /* Check execute permissions */
    if (!(st.st_mode & S_IXUSR))
    {
        fprintf(stderr, "./hsh: 1: %s: Permission denied\n", args[0]);
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execve(args[0], args, environ) == -1)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* Forking error */
        perror("./hsh");
    }
    else
    {
        /* Parent process */
        waitpid(pid, &status, WUNTRACED);
        fflush(stdout); /* Ensure output is flushed */
    }

    return (1);
}
