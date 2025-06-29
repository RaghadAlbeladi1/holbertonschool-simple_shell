#include "shell.h"
#include <string.h>
#include <stdlib.h>

/**
 * read_command - Reads a line of input from stdin.
 * Return: Pointer to the command string, or NULL on EOF.
 */
char *read_command(void)
{
char *command = NULL;
size_t len = 0;
if (getline(&command, &len, stdin) == -1)
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
 * split_command - Splits a command into tokens (handles arguments).
 * @command: The command string.
 * Return: NULL~@~Qterminated array of tokens.
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
bufsize *= 2;
char **tmp = realloc(tokens, sizeof(char *) * bufsize);
if (!tmp)
{
free(tokens);
exit(EXIT_FAILURE);

}
tokens = tmp;
}
token = strtok(NULL, SHELL_TOK_DELIM);
}
tokens[pos] = NULL;
return (tokens);
}
