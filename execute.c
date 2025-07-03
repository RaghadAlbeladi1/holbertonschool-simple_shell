#include "shell.h"

/**
 * execute_command - Executes a shell command using fork and execvp
 * @command: The command string to execute
 *
 * Return: Exit status of the executed command:
 *         - 127 for command not found
 *         - 126 for permission denied
 *         - Actual status from executed command
 *         - 1 for other errors
 */
int execute_command(const char *command)
{
    pid_t child_pid;
    int status;
    char *args[128];
    char command_copy[1024];
    int arg_count = 0;
    char *token;

    if (command == NULL || *command == '\0')
        return (0);

    child_pid = fork();
    if (child_pid == -1)
    {
        print_message("Error forking process.\n");
        return (1);
    }
    else if (child_pid == 0)
    {

        strncpy(command_copy, command, sizeof(command_copy) - 1);
        command_copy[sizeof(command_copy) - 1] = '\0';

        token = strtok(command_copy, " ");
        while (token != NULL && arg_count < 127)
        {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;


        if (access(args[0], F_OK) == -1)
        {
            print_message(args[0]);
            print_message(": command not found\n");
            exit(127);
        }
        else if (access(args[0], X_OK) == -1)
        {
            print_message(args[0]);
            print_message(": Permission denied\n");
            exit(126);
        }

        execvp(args[0], args);

        perror(args[0]);
        exit(127);
    }
    else
    {

        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            return (128 + WTERMSIG(status));
        else
            return (1);
    }
}
