#include "shell.h"

/**
 * find_in_path - Finds a command in PATH
 * @cmd: Command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_in_path(char *cmd)
{
    char *path, *path_copy, *dir, *full_path;
    int cmd_len, dir_len;

    if (!cmd)
        return NULL;

    /* Check if command exists in current directory */
    if (access(cmd, X_OK) == 0)
        return strdup(cmd);

    path = getenv("PATH");
    if (!path)
        return NULL;

    path_copy = strdup(path);
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
