#include "shell.h"

/**
 * read_command - Reads a command from standard input
 * @command: Buffer to store the command
 * @size: Size of the buffer
 */
void read_command(char *command, size_t size)
{
	ssize_t nread;
	char *line = NULL;
	size_t len = 0;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		print_message("\n");
		free(line);
		exit(EXIT_SUCCESS);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	strncpy(command, line, size - 1);
	command[size - 1] = '\0';

	free(line);
}

