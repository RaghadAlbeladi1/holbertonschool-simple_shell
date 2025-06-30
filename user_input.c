#include "shell.h"

/**

* get_input - reads a line of input from the user
*
* Return: pointer to the input string, or NULL on EOF or error
*/
char *get_input(void)
{
char *line = NULL;
size_t len = 0;
ssize_t read;

read = getline(&line, &len, stdin);
if (read == -1)
{
free(line);
return (NULL);
}
return (line);
}

/**
* tokenize_input - splits a line into tokens (command and arguments)
* @line: the input string
*
* Return: pointer to array of strings (tokens), NULL on failure
*/
char **tokenize_input(char *line)
{
int bufsize = 64, i = 0;
char *token;
char **tokens = malloc(bufsize * sizeof(char *));
char **tmp;

if (!tokens)
{
perror("malloc failed");
exit(EXIT_FAILURE);
}

token = strtok(line, " \n");
while (token != NULL)
{
tokens[i++] = token;

if (i >= bufsize)
{
bufsize += 64;
tmp = realloc(tokens, bufsize * sizeof(char *));
if (!tmp)
{
free(tokens);
perror("realloc failed");
exit(EXIT_FAILURE);

}
tokens = tmp;
}

token = strtok(NULL, " \n");
}
tokens[i] = NULL;

return (tokens);
}

