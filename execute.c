#include "shell.h"

/**
 * run_command - Forks and executes a command.
 * @args: NULL-terminated array of arguments.
 *
 * Return: Exit status of the executed command.
 */
int run_command(char **args)
{
	pid_t pid;
	int status = 1, child_status;

	/* إذا لا يوجد أمر */
	if (args[0] == NULL)
		return (status);

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
		return (EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &child_status, 0) == -1)
			perror("simple_shell");
		else if (WIFEXITED(child_status))
			status = WEXITSTATUS(child_status);
	}

	return (status);
}

