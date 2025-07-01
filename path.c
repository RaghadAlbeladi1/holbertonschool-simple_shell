#include "shell.h"

/**
 * _getpath - Gets PATH from environ
 * Return: PATH string or NULL
 */
char *_getpath(void)
{
    char **env = environ;
    while (*env)
    {
        if (strncmp(*env, "PATH=", 5) == 0)
            return (*env + 5);
        env++;
    }
    return NULL;
}

/**
 * find_in_path - Finds command in PATH
 * @cmd: Command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_in_path(char *cmd)
{
    char *path, *path_copy, *dir, *full_path;
    size_t dir_len, cmd_len;

    if (!cmd || !*cmd) return NULL;

    /* Check current directory first */
    if (access(cmd, X_OK) == 0)
        return strdup(cmd);

    path = _getpath();
    if (!path) return NULL;

    path_copy = strdup(path);
    if (!path_copy) return NULL;

    cmd_len = strlen(cmd);
    dir = strtok(path_copy, ":");

    while (dir)
    {
        dir_len = strlen(dir);
        full_path = malloc(dir_len + cmd_len + 2);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }

        sprintf(full_path, "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0)
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
