#include "shell.h"

/**
 * execute - Executes a command with its arguments.
 * @args: Null-terminated array of command arguments.
 *
 * Return: 1 to continue shell execution, 0 to exit.
 *
 * Description: Forks a child process to execute the command.
 * Handles execution errors and prints appropriate messages.
 * Parent process waits for child to complete.
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	if (!args[0])
		return (1);

	pid = fork();
	if (pid == -1)
	{
		perror("./shell");
		return (1);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "./shell: No such file or directory\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
		}
	}

	return (1);
}
