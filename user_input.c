#include "shell.h"

/**
 * read_command - Reads a line from stdin and strips the newline.
 *
 * Return: Pointer to the cleaned command string, or NULL on EOF.
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

	command[strcspn(command, "\n")] = '\0';

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
 *
 * Return: NULL-terminated array of tokens.
 */
char **split_command(char *command)
{
	int bufsize = 64, pos = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token;

	if (!tokens)
		exit(EXIT_FAILURE);

	token = strtok(command, SHELL_TOK_DELIM);
	while (token)
	{
		tokens[pos++] = token;

		if (pos >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (!tokens)
				exit(EXIT_FAILURE);
		}
		token = strtok(NULL, SHELL_TOK_DELIM);
	}

	tokens[pos] = NULL;
	return (tokens);
}

