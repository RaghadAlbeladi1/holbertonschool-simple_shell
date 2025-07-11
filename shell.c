#include "shell.h"

int last_status = 0;
/**
 * main - Entry point for the simple shell
 *
 * Return: Exit status of the shell
 */
int main(void)
{
	char *line = NULL;
	char **args = NULL;
	size_t len = 0;
	ssize_t read;
	int status = 1;
	int interactive_mode = isatty(STDIN_FILENO) && isatty(STDERR_FILENO);
	int builtin_status;

	while (1) /* Infinite loop, breaks only on EOF or exit */
	{
		if (interactive_mode)
			display_prompt(); /* Display the prompt ("$ ") */

		read = getline(&line, &len, stdin); /* Read user input */

		if (read == -1)
			break;

		args = split_line(line); /* Split the input line*/


		builtin_status = handle_builtin(args, line);
		if (builtin_status == 0 || builtin_status == 1)
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
