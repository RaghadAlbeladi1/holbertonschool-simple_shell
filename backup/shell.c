#include "shell.h"

/**
 * main - Entry point for simple shell
 * Return: EXIT_SUCCESS on success
 */
int main(void)
{
	shell_loop();
	return (EXIT_SUCCESS);
}

/**
 * shell_loop - Main shell processing loop
 */
void shell_loop(void)
{
	char *line = NULL;
	char **args = NULL;
	int status = 1;

	while (status) {
		if (isatty(STDIN_FILENO))
			print_prompt();

		line = read_line();
		if (!line) {
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		args = parse_line(line);
		if (args) {
			status = execute(args);
			free(args);
		}
		free(line);
	}
}
