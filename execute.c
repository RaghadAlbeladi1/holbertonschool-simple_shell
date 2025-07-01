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
 * find_path - Locates command in PATH
 * @cmd: Command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_path(char *cmd)
{
    char *path = getenv("PATH");
    char *path_copy, *dir, *full_path;
    struct stat st;

    if (!path)
        return NULL;

    path_copy = strdup(path);
    dir = strtok(path_copy, ":");

    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        sprintf(full_path, "%s/%s", dir, cmd);

        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
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
    char *full_path = NULL;

    if (args[0] == NULL)
        return (1);

    if (_strcmp(args[0], "exit") == 0)
        return (0);

    if (_strcmp(args[0], "env") == 0)
    {
        char **env = environ;
        while (*env)
            printf("%s\n", *env++);
        return (1);
    }

    /* Check if command contains path */
    if (strchr(args[0], '/'))
    {
        if (stat(args[0], &st) == -1)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            return (1);
        }
        full_path = strdup(args[0]);
    }
    else
    {
        full_path = find_path(args[0]);
        if (!full_path)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            return (1);
        }
    }

    if (!(stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR)))
    {
        fprintf(stderr, "./hsh: 1: %s: Permission denied\n", args[0]);
        free(full_path);
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(full_path, args, environ) == -1)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            free(full_path);
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

    free(full_path);
    return (1);
}
