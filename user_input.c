#include "shell.h"

/**
 * read_command - Reads a line from stdin, strips the newline.
 * Return: pointer to malloc’d string, or NULL on EOF.
 */
char *read_command(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&command, &len, stdin);
	if (nread == -1)
	{
		free(command);
		return (NULL);
	}

	/* Remove trailing newline */
	command[strcspn(command, "\n")] = '\0';

	/* If empty or only spaces/tabs, return an empty buffer */
	if (command[0] == '\0' ||
		strspn(command, " \t") == strlen(command))
	{
		free(command);
		return (strdup(""));
	}

	return (command);
}

/**
 * split_command - Splits a command string into tokens.
 * @command: The command string.
 * Return: NULL terminated array of tokens.
 */
char **split_command(char *command)
{
	int bufsize = 64, pos = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token;

	if (tokens == NULL)
		exit(EXIT_FAILURE);

	token = strtok(command, SHELL_TOK_DELIM);
	while (token)
	{
		tokens[pos++] = token;
		if (pos >= bufsize)
		{
			bufsize *= 2;
			tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (tokens == NULL)
				exit(EXIT_FAILURE);
		}
		token = strtok(NULL, SHELL_TOK_DELIM);
	}
	tokens[pos] = NULL;
	return (tokens);
}

