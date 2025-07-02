#include "shell.h"

/**
 * main - Shell loop
 * Return: 0 on success
 */
int main(void)
{
	char command[120];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			display_prompt();

		read_command(command, sizeof(command));

		if (command[0] == '\0')
			continue;


		if (handle_builtin(command))
			continue;

		execute_command(command);
	}

	return (0);
}

