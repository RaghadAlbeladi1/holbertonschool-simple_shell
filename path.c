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
    char *dir;  /* Removed unused full_path variable */
    static char buffer[1024];

    if (!path || !cmd)
        return NULL;

    /* Make copy of PATH string */
    path = strdup(path);
    if (!path)
        return NULL;

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
