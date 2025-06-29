#include "shell.h"

/**
 * run_command - Forks and executes a command.
 * @args: NULL~@~Qterminated array of arguments.
 *
 * Return: Exit status of the executed command.
 */
int run_command(char **args)
{
pid_t pid;
int   status;
pid = fork();
if (pid == 0)
{
if (execve(args[0], args, environ) == -1)
{
perror("simple_shell");
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{
perror("simple_shell");
}
else
{
waitpid(pid, &status, 0);
}
return (status);
}
