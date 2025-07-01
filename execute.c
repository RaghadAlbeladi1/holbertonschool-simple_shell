#include "shell.h"
#include <sys/stat.h>
#include <sys/wait.h>

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 if equal, difference otherwise
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

/**
 * execute - Executes a command with arguments
 * @args: Null-terminated array of arguments
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args)
{
    pid_t pid;
    int status;
    struct stat st;

    if (args[0] == NULL)
        return (1);

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
        if (execve(args[0], args, environ) == -1)
        {
            perror("./hsh");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    return (1);
}
