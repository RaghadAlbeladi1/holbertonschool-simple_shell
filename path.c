#include "shell.h"

/**
 * find_in_path - Finds a command in PATH.
 * @cmd: Command to find.
 * Return: Full path if found, NULL otherwise.
 */
char *find_in_path(char *cmd)
{
    char *path = getenv("PATH");
    char *path_copy, *dir, *full_path;

    if (!path)
        return NULL;

    path_copy = strdup(path);
    dir = strtok(path_copy, ":");
    full_path = malloc(BUFSIZE);

    while (dir)
    {
        snprintf(full_path, BUFSIZE, "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }
        dir = strtok(NULL, ":");
    }

    free(full_path);
    free(path_copy);
    return NULL;
}
