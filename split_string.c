#include "shell.h"

/**
 * split_string - split a string into an array of strings
 * @command: the command entered
 * Return: args (array of the command written)
 */
char **split_string(char *command)
{
	char **args = malloc(sizeof(char *) * BUFF_SIZE);
	char *token;
	size_t i = 0, j = 0;


	if (!args)
		return (NULL);

	token = strtok(command, " \n\t");

	if (!token)
	{
		free(args);
		return (NULL);
	}

	while (token)
	{
		args[i] = strdup(token);
		if (!args[i])
		{
			for (; j < i; j++)
				free(args[j]);
			free(args);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \n\t");
	}
	args[i] = NULL;

return (args);
}
