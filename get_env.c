#include "shell.h"
/**
 * _getenv - Find the vamue of the environnement var
 * @name: name of the env to find
 * @environ: Environment list
 * Return: the env or NULL
 */

char *_getenv(const char *name, char **environ)
{
	int len, i;
	char *env;

	if (name == NULL || environ == NULL)
		return (NULL);

	len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0)
		{
			env = environ[i] + len + 1;
			return (env);
		}
	}
return (NULL);
}
