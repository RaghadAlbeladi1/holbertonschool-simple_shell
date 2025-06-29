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
 * shell_loop - The main loop of the shell.
 * Continuously prompts the user for input, reads the command,
 * parses it into arguments, and executes it.
 */
void shell_loop(void)
{
	char *command = NULL;
	char **args = NULL;

	while (1)
	{
		print_prompt();

		command = read_command();
		if (command == NULL)
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
		run_command(args);

		free(args);
		free(command);
	}
}

