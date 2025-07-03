#include "shell.h"

/**
 * print_env - print all the environment
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * exec_builtin - handle execution of the built in "exit" and "env"
 * @args: array of arguments received
 * Return: 1 if ok 0 if fails
 */

int exec_builtin(char **args)
{
	if (!args)
		return (0);

	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	if (strcmp(args[0], "exit") == 0 && args[1] != NULL)
		return (1);

	return (0);
}
