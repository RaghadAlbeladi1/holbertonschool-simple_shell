#include "shell.h"

/**
 * hsh_tokenizer - Split the input string into a array of arguments (tokens)
 * @input: String from input (main function)
 * Return: Pointer to the array of tokens
 */
char **hsh_tokenizer(char *input)
{
	int buffer = BUFSIZE, newBuffer = 0, position = 0;
	char **tokens = NULL, *token = NULL;
	char **backup_tokens = NULL;

	tokens = malloc(buffer * sizeof(char *));
	if (tokens == NULL)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, DELIM_I);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;


		if (position >= buffer)
		{
			newBuffer = BUFSIZE * 2;
			backup_tokens = tokens;
			tokens = _realloc(tokens, buffer, newBuffer * sizeof(char *));
			if (tokens == NULL)
			{
				free(backup_tokens);
				free(tokens);
				fprintf(stderr, "memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIM_I);
	}

	tokens[position] = NULL;
	return (tokens);
}

/**
 * tokenizer_path - Split the environment variable PATH into an array of tokens
 * @input: Pointer to environment variable PATH
 * Return: Pointer to the array of tokens
 */
char **tokenizer_path(char *input)
{
	int buffer = BUFSIZE, newBuffer = 0, position = 0;
	char **tokens = NULL, *token = NULL;
	char **backup_tokens = NULL;


	tokens = malloc(buffer * sizeof(char *));
	if (tokens == NULL)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, DELIM_P);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;


		if (position >= buffer)
		{
			newBuffer = BUFSIZE * 2;
			backup_tokens = tokens;
			tokens = _realloc(tokens, buffer, newBuffer * sizeof(char *));
			if (tokens == NULL)
			{
				free(backup_tokens);
				free(tokens);
				fprintf(stderr, "memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIM_P);
	}

	tokens[position] = NULL;
	return (tokens);
}
