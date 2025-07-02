#include "shell.h"

int execute(char **args) {
    pid_t pid;
    int status;
    char *full_path = NULL;

    if (!args || !args[0]) return 1;

    if (handle_builtins(args)) return 1;

    if (strchr(args[0], '/') == NULL) {
        full_path = find_in_path(args[0]);
        if (!full_path) {
            fprintf(stderr, "%s: 1: %s: not found\n", "hsh", args[0]);
            return 1;
        }
        args[0] = full_path;
    }

    pid = fork();
    if (pid == 0) {
        execve(args[0], args, environ);
        perror("execve failed");
        if (full_path && full_path != args[0]) free(full_path);
        _exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed");
        if (full_path && full_path != args[0]) free(full_path);
        return 1;
    } else {
        waitpid(pid, &status, 0);
    }

    if (full_path && full_path != args[0]) free(full_path);
    return 1;
}
