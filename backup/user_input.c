#include "shell.h"

/**
 * read_line - Reads input from stdin
 * Return: Pointer to input string
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1) {
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * parse_line - Splits input into tokens
 * @line: Input string
 * Return: Null-terminated array of tokens
 */
char **parse_line(char *line)
{
	int bufsize = BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens) {
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, DELIM);
	while (token) {
		tokens[position++] = token;
		if (position >= bufsize) {
			bufsize += BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens) {
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}
