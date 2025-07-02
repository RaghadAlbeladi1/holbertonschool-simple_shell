#include "shell.h"

/**
 * main - Main loop, recieve input from CLI parse and execute it
 * @argc: Number of arguments passed to the program
 * @argv: Array of arguments
 * Return: Always 0 on success
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	char **arguments = NULL;
	char *input_stdin = NULL;
	int status_return = 1, exit_status = 0;
	size_t size = 0;
	ssize_t n = 0;

	while (status_return && n != EOF)
	{
		size = 0;

		status_return = isatty(STDIN_FILENO);
		if (status_return)
			write(STDOUT_FILENO, "#(ಠ_ಠ)->$ ", 14);

		signal(SIGINT, sigintH);

		n = getline(&input_stdin, &size, stdin);
		if (n == -1)
		{
			free(input_stdin);
			break;
		}

		if (validate_spaces(input_stdin))
		{
			free(input_stdin);
			continue;
		}

		arguments = hsh_tokenizer(input_stdin);
		if (*arguments[0] == '\0')
			continue;

		status_return = hsh_execute_builtins(arguments, input_stdin,
				argv, &exit_status);
		free(input_stdin);
		free(arguments);
	}
	return (0);
}
