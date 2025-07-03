#include "shell.h"

/**
 * main - Entry point for simple shell
 * Handles both interactive and non-interactive modes
 *
 * Return: Final shell exit status
 */
int main(void)
{
	char *line = NULL;
	char **args = NULL;
	size_t len = 0;
	int status = 1;
	int interactive_mode = isatty(STDIN_FILENO);
	int builtin_status;

	while (1)
	{
		if (interactive_mode)
			display_prompt();

		if (getline(&line, &len, stdin) == -1)
			break;

		args = split_line(line);
		if (!args)
			continue;

		builtin_status = handle_builtin(args, line);
		if (builtin_status >= 0)
		{
			status = builtin_status;
			free(args);
			continue;
		}

		status = execute_command(args);
		last_status = status;
		free(args);
	}

	free(line);
	return (status);
}
