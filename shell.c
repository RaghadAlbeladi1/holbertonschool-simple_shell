#include "shell.h"

/**
 * main - Entry point for simple shell.
 * Return: Always EXIT_SUCCESS.
 */
int main(void)
{
	shell_loop();
	return (EXIT_SUCCESS);
}

/**
 * shell_loop - Main shell processing loop (REPL).
 */
void shell_loop(void)
{
	char *line = NULL;
	char **args = NULL;
	int status = 1;

	while (status)
	{
		print_prompt();
		line = read_line();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		args = parse_line(line);
		if (args)
		{
			status = execute(args);
			free(args);
		}
		free(line);
	}
}
