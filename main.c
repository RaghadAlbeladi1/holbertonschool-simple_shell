#include "shell.h"

/**
 * main - main fucntion to launch our simple shell
 * Return: 0 at the end
 */

int main(void)
{
	char *input, **args;

	signal(SIGINT, handle_sigint);
	while (1)
	{
		prompt();
		input = read_input();
		if (!input)
			break;
		if (strcmp(input, "\n") == 0 || strlen(input) == 0)
		{
			free(input);
			continue;
		}
		if (input[strlen(input) - 1] == '\n')
			input[strlen(input) - 1] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0);
		}
		args = split_string(input);
		if (!args)
		{
			free(input);
			continue;
		}
		execute_command(args);
		free(input);
		free_ressources(args);
	}
return (0);
}
