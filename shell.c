#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


extern char **environ;

/**
 * execute - Executes a command with arguments.
 * @args: Null-terminated array of arguments.
 * Return: 1 to continue, 0 to exit.
 */
int execute(char **args)
{
    pid_t pid;
    int status;

    if (!args[0])
        return (1);
    if (strcmp(args[0], "exit") == 0)
        return (0);
    if (strcmp(args[0], "env") == 0)
    {
        char **env = environ;
        while (*env)
            printf("%s\n", *env++);
        return (1);
    }
    pid = fork();
    if (pid == 0)
    {
        if (execve(args[0], args, environ) == -1)
        {
            fprintf(stderr, "./shell: No such file or directory\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    return (1);
}

/**
 * main - Entry point for simple shell.
 * Return: Always EXIT_SUCCESS.
 */
int main(void)
{
    shell_loop();
    return (EXIT_SUCCESS);
}

/**
 * shell_loop - Main shell processing loop (REPL).
 */
void shell_loop(void)
{
    char *line = NULL;
    char **args = NULL;
    int status = 1;

    while (status)
    {
        print_prompt();
        line = read_line();
        if (!line)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }
        args = parse_line(line);
        if (args)
        {
            status = execute(args);
            free(args);
        }
        free(line);
    }

}
