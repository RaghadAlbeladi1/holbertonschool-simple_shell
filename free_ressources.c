#include "shell.h"
/**
 * free_ressources - free the array args received
 * @args: Array received
 */

void free_ressources(char **args)
{
	size_t i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
