#include "shell.h"

/**
 * run_command - Forks and executes a command using execvp.
 * @args: Null-terminated array of command and its arguments.
 *
 * Return: Always returns 1 to continue the shell loop.
 */
int run_command(char **args)
{
	pid_t pid;
	int child_status;

	if (args[0] == NULL)
		return (1);

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
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
		if (waitpid(pid, &child_status, 0) == -1)
			perror("simple_shell");
	}

	return (1);
}

