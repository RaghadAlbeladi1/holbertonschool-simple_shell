#include "shell.h"

/* Array of built-in commands */
builtin_t builtins[] = {
    {"exit", shell_exit},
    {"env", shell_env},
    {"cd", shell_cd},
    {NULL, NULL}
};

int execute(char **args)
{
    int i;

    if (args[0] == NULL)
        return (1);

    for (i = 0; builtins[i].name != NULL; i++)
    {
        if (_strcmp(args[0], builtins[i].name) == 0)
            return (builtins[i].func(args, environ));
    }

    return (execute_external(args, environ));
}

int execute_external(char **args, char **env)
{
    pid_t pid;
    int status;
    char *full_path = find_path(args[0], env);

    if (!full_path)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(full_path, args, env) == -1)
        {
            perror("execve error");
            free(full_path);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork error");
        free(full_path);
    }
    else
    {
        waitpid(pid, &status, WUNTRACED);
    }

    free(full_path);
    return (1);
}

int shell_exit(char **args, char **env)
{
    int status = 0;
    (void)env;

    if (args[1])
        status = _atoi(args[1]);

    free_tokens(args);
    exit(status);
}

int shell_env(char **args, char **env)
{
    int i;
    (void)args;

    for (i = 0; env[i]; i++)
        printf("%s\n", env[i]);

    return (1);
}
