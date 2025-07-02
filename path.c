#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * find_in_path - Finds a command in PATH
 * @cmd: Command to find
 * Return: Full path or NULL
 */
char *find_in_path(char *cmd)
{
    char *path = _getpath();
    char *dir, *full_path;
    static char buffer[1024];

    if (!path)
        return NULL;

    /* Make copy of PATH string */
    path = strdup(path);
    dir = strtok(path, ":");

    while (dir)
    {
        snprintf(buffer, sizeof(buffer), "%s/%s", dir, cmd);
        if (access(buffer, X_OK) == 0)
        {
            free(path);
            return buffer;
        }
        dir = strtok(NULL, ":");
    }

    free(path);
    return NULL;
}
