#include "shell.h"

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always EXIT_SUCCESS.
 */
int main(void)
{
	shell_loop();
	return (EXIT_SUCCESS);
}

/**
 * shell_loop - Main loop reading and executing commands.
 */
void shell_loop(void)
{
	char *command;
	char **args;
	int status = 1;

	while (status)
	{
		print_prompt();
		command = read_command();
		if (command == NULL)  /* Ctrl+D */
		{
			putchar('\n');
			break;
		}
		if (command[0] == '\0')
		{
			free(command);
			continue;
		}

		args = split_command(command);

		if (args[0] == NULL)
		{
			free(args);
			free(command);
			continue;
		}


		status = run_command(args);

		free(args);
		free(command);
	}
}

