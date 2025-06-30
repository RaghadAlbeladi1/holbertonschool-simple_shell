#include "shell.h"

/**
* handle_builtins - handles built-in commands like exit and env
* @args: array of arguments
* @env: environment variables
*
* Return: 1 if a built-in command was handled, 0 otherwise
*/
int handle_builtins(char **args, char **env)
{
	int i;

	if (strcmp(args[0], "exit") == 0) {
		exit(0);
	}

	if (strcmp(args[0], "env") == 0) {
		for (i = 0; env[i] != NULL; i++) {
			write(STDOUT_FILENO, env[i], strlen(env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}

	return (0);
}

