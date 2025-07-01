#include "shell.h"

/**
 * execute - Main command execution function.
 * @args: Array of command and arguments.
 * Return: 1 to continue, 0 to exit.
 */
int execute(char **args)
{
    if (args[0] == NULL)
        return (1);

    if (_strcmp(args[0], "exit") == 0)
        return (handle_exit(args));

    if (_strcmp(args[0], "env") == 0)
        return (handle_env());

    return (execute_external(args));
}

/**
 * execute_external - Executes external programs.
 * @args: Command and arguments array.
 * Return: 1 on success, 0 on failure.
 */
int execute_external(char **args)
{
    pid_t pid;
    int status;
    char *full_path = find_path(args[0]);

    if (!full_path)
    {
        print_error(args[0], "not found");
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(full_path, args, environ) == -1)
        {
            print_error(args[0], NULL);
            free(full_path);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        print_error("fork", NULL);
        free(full_path);
    }
    else
    {
        waitpid(pid, &status, WUNTRACED);
    }

    free(full_path);
    return (1);
}

/**
 * find_path - Locates command in PATH.
 * @command: Command to locate.
 * Return: Full path if found, NULL otherwise.
 */
char *find_path(char *command)
{
    char *path, *path_copy, *dir, *full_path;
    struct stat st;

    if (_strchr(command, '/'))
    {
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
            return (_strdup(command));
        return (NULL);
    }

    path = _getenv("PATH");
    if (!path)
        return (NULL);

    path_copy = _strdup(path);
    dir = _strtok(path_copy, ":");

    while (dir)
    {
        full_path = build_path(dir, command);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }

        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free(path_copy);
            return (full_path);
        }

        free(full_path);
        dir = _strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

/**
 * build_path - Constructs full path from directory and command.
 * @dir: Directory path.
 * @command: Command name.
 * Return: Allocated full path string.
 */
char *build_path(char *dir, char *command)
{
    char *full_path;
    int len = _strlen(dir) + _strlen(command) + 2;

    full_path = malloc(sizeof(char) * len);
    if (!full_path)
        return (NULL);

    _sprintf(full_path, "%s/%s", dir, command);
    return (full_path);
}

/**
 * handle_exit - Handles exit command.
 * @args: Arguments array.
 * Return: 0 to exit.
 */
int handle_exit(char **args)
{
    int status = 0;

    if (args[1])
        status = _atoi(args[1]);

    free_tokens(args);
    exit(status);
}

/**
 * handle_env - Prints environment variables.
 * Return: Always 1.
 */
int handle_env(void)
{
    int i;

    for (i = 0; environ[i]; i++)
        _puts(environ[i]);

    return (1);
}

/**
 * print_error - Prints formatted error message.
 * @command: Failed command.
 * @message: Custom error message.
 */
void print_error(char *command, char *message)
{
    char *shell_name = _getenv("_");

    if (!shell_name)
        shell_name = "hsh";

    _fprintf(stderr, "%s: 1: %s", shell_name, command);
    
    if (message)
        _fprintf(stderr, ": %s\n", message);
    else
        perror("");
}
