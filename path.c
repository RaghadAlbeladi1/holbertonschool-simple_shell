#include "shell.h"

char *_getpath(void) {
    char **env = environ;
    while (*env) {
        if (strncmp(*env, "PATH=", 5) == 0)
            return (*env + 5);
        env++;
    }
    return NULL;
}

char *find_in_path(char *cmd) {
    if (!cmd || !*cmd) return NULL;

    char *path = _getpath();
    if (!path) return NULL;

    char *path_copy = strdup(path);
    if (!path_copy) return NULL;

    char *full_path = NULL;
    char *dir = strtok(path_copy, ":");

    while (dir) {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        if (!full_path) {
            free(path_copy);
            return NULL;
        }

        sprintf(full_path, "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
