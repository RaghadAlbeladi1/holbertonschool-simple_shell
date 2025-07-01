#include "shell.h"

/**
 * execute - Executes a command with arguments
 * @args: Null-terminated array of arguments
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args)
{
    pid_t pid;
    int status;
    char *full_path = NULL;

    if (!args || !args[0])
        return 1;

    /* Handle builtins */
    if (handle_builtins(args))
        return 1;

    /* Handle PATH */
    if (strchr(args[0], '/') == NULL)
    {
        full_path = find_in_path(args[0]);
        if (!full_path)
        {
            fprintf(stderr, "%s: 1: %s: not found\n", "hsh", args[0]);
            return 1;
        }
        args[0] = full_path;
    }

    /* Fork and execute */
    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execve(args[0], args, environ) == -1)
        {
            perror("execve error");
            if (full_path && full_path != args[0])
                free(full_path);
            _exit(EXIT_FAILURE);  // استخدام _exit بدل exit في العمليات الفرعية
        }
    }
    else if (pid < 0)
    {
        /* Fork failed */
        perror("fork error");
        if (full_path && full_path != args[0])
            free(full_path);
        return 1;
    }
    else
    {
        /* Parent process */
        waitpid(pid, &status, 0);
    }

    /* Cleanup */
    if (full_path && full_path != args[0])
        free(full_path);

    return 1;
}
