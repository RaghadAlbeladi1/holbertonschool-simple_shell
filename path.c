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

    printf("=== DEBUG START: find_in_path() ===\n");
    printf("DEBUG: Command to find: '%s'\n", cmd);

    if (!cmd) {
        printf("DEBUG: Null command received\n");
        return NULL;
    }

    /* Check if command exists in current directory */
    printf("DEBUG: Checking current directory for command...\n");
    if (access(cmd, X_OK) == 0) {
        printf("DEBUG: Found in current directory: '%s'\n", cmd);
        return strdup(cmd);
    }

    path = getenv("PATH");
    printf("DEBUG: PATH variable: '%s'\n", path ? path : "(null)");

    if (!path) {
        fprintf(stderr, "DEBUG: PATH environment variable not set\n");
        return NULL;
    }

    path_copy = strdup(path);
    cmd_len = strlen(cmd);
    dir = strtok(path_copy, ":");

    while (dir)
    {
        printf("DEBUG: Checking directory: '%s'\n", dir);
        
        dir_len = strlen(dir);
        full_path = malloc(dir_len + cmd_len + 2);
        if (!full_path)
        {
            printf("DEBUG: Memory allocation failed\n");
            free(path_copy);
            return NULL;
        }

        sprintf(full_path, "%s/%s", dir, cmd);
        printf("DEBUG: Trying path: '%s'\n", full_path);

        if (access(full_path, X_OK) == 0)
        {
            printf("DEBUG: Found at: '%s'\n", full_path);
            free(path_copy);
            return full_path;
        }

        printf("DEBUG: Not found in: '%s'\n", full_path);
        free(full_path);
        dir = strtok(NULL, ":");
    }

    printf("DEBUG: Command not found in any PATH directory\n");
    free(path_copy);
    printf("=== DEBUG END: find_in_path() ===\n");
    return NULL;
}
