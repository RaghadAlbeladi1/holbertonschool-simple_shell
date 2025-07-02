#include "shell.h"
#include <sys/wait.h>
#include <unistd.h>

int execute(char **args)
{
    pid_t pid;
    int status;

    if (args[0] == NULL)
        return 1;

    /* Built-ins handle their own memory */
    if (handle_builtins(args))
        return 1;

    /* External commands */
    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("hsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("hsh");
    } else {
        waitpid(pid, &status, WUNTRACED);
    }

    return 1;
}
