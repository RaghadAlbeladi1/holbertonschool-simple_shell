#include "shell.h"

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
