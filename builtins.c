#include "shell.h"

/**
 * handle_builtin - Check and execute built-in commands
 * @command: Input command string
 * Return: 1 if it's a builtin and was handled, 0 otherwise
 */
int handle_builtin(char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(command, "env") == 0)
	{
		extern char **environ;
		int i = 0;

		while (environ[i])
		{
			print_message(environ[i]);
			print_message("\n");
			i++;
		}
		return (1);
	}

	return (0);
}
