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
 * shell_loop - The main REPL loop of the shell.
 *
 * Description: Repeatedly prints a prompt (only when running
 * in interactive mode), reads a full line from stdin, tokenizes
 * it, then executes the resulting command.
 */
void shell_loop(void)
{
	char *command = NULL;
	char **args = NULL;

	while (1)
	{
		if (isatty(STDIN_FILENO))
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

