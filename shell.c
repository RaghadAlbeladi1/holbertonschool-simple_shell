#include "shell.h"

/**
 * main - Entry point of the shell
 * Return: Always 0 on success
 */
int main(void)
{
	char command[120];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			display_prompt();

		read_command(command, sizeof(command));
		execute_command(command);
	}

	return (0);
}

