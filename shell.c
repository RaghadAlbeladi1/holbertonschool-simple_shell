#include "shell.h"

/*
 * FIX: Checker compliance
 * - Prevent prompt in non-interactive mode
 * - Avoid printing \n at EOF if not interactive
 * - Ignore lines made of only spaces/tabs
 * - Trim whitespace properly before processing
 */

static void trim_whitespace(char *s);

/**
 * main - Entry point for the shell
 *
 * Return: Always EXIT_SUCCESS
 */
int main(void)
{
	shell_loop();
	return (EXIT_SUCCESS);
}

/**
 * shell_loop - Main REPL loop of the shell
 *
 * Description: Prompts user, reads command, trims and tokenizes it,
 * and then executes it. Handles interactive/non-interactive modes properly.
 */
void shell_loop(void)
{
	char *command = NULL, **args = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			print_prompt();

		nread = getline(&command, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				putchar('\n');
			break;
		}

		command[strcspn(command, "\n")] = '\0';
		trim_whitespace(command);

		if (*command == '\0')
			continue;

		args = split_command(command);
		if (args && args[0])
			run_command(args);

		free(args);
	}
	free(command);
}

/**
 * trim_whitespace - Removes leading and trailing spaces/tabs in-place
 * @s: The string to trim
 */
static void trim_whitespace(char *s)
{
	char *end;

	while (*s && (*s == ' ' || *s == '\t'))
		s++;

	end = s + strlen(s) - 1;
	while (end > s && (*end == ' ' || *end == '\t'))
		*end-- = '\0';

	if (s != command)
		memmove(command, s, strlen(s) + 1);
}

