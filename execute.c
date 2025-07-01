#include "shell.h"
#include <sys/stat.h>
#include <sys/wait.h>

/**
 * _strcmp - Custom string comparison
 * @s1: First string
 * @s2: Second string
 * Return: 0 if equal, difference otherwise
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

/**
 * execute - Executes a command
 * @args: Array of arguments
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args)
{
    pid_t pid;
    int status;
    struct stat st;

    if (args[0] == NULL)
        return (1);

    /* Handle builtins */
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

    /* Check execute permission */
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
            fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("./hsh");
    }
    else
    {
        waitpid(pid, &status, WUNTRACED);
    }

    return (1);
}
