#include "shell.h"

/**
 * read_command - Reads a line of input from stdin.
 *
 * Return: Pointer to the command string, or NULL on EOF.
 */
char *read_command(void)
{
char *command = NULL;
size_t cmdsize = 0;
if (getline(&command, &cmdsize, stdin) == -1)
{
free(command);
return (NULL);
}
return (command);
}
/**
 * split_command - Splits a command into tokens (handles arguments).
 * @command: The command string.
 *
 * Return: NULL~@~Qterminated array of tokens.
 */
char **split_command(char *command)
{
int bufsize = 64;
int position = 0;
char **tokens = malloc(sizeof(char *) * bufsize);
char *token;
if (!tokens)
exit(EXIT_FAILURE);
token = strtok(command, SHELL_TOK_DELIM);
while (token != NULL)
{
tokens[position++] = token;
if (position >= bufsize)
{
bufsize *= 2;
tokens = realloc(tokens, sizeof(char *) * bufsize);
if (!tokens)
exit(EXIT_FAILURE);
}
token = strtok(NULL, SHELL_TOK_DELIM);
}
tokens[position] = NULL;
return (tokens);
}
