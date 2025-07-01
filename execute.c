#include "shell.h"

/**
 * execute - Determines if command is built-in or external.
 * @args: Argument array.
 * Return: 1 to continue, 0 to exit.
 */
int execute(char **args)
{
	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (shell_exit(args));
	if (strcmp(args[0], "env") == 0)
		return (shell_env(args));

	return (launch(args));
}

/**
 * launch - Executes external commands.
 * @args: Argument array.
 * Return: Always 1 (continue).
 */
int launch(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

/**
 * shell_exit - Handles the exit built-in.
 * @args: Arguments (unused).
 * Return: 0 (exit).
 */
int shell_exit(char **args)
{
	(void)args;
	return (0);
}

/**
 * shell_env - Prints the environment.
 * @args: Arguments (unused).
 * Return: Always 1 (continue).
 */
int shell_env(char **args)
{
	char **env = environ;

	(void)args;
	while (*env)
		printf("%s\n", *env++);
	return (1);
}
