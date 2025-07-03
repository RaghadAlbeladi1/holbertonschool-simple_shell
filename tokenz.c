#include "shell.h"
/**
 * find_executable - search iof the command exists in PATH
 * @command: command received in argv[0] to find
 * Return: the full path of the command
 */
char *find_executable(char *command)
{
	char *path = _getenv("PATH", environ);
	char *path_copy, *token, *full_path;
	size_t len;

	if (access(command, X_OK) == 0) /** check if the commandcan be executed*/
		return (strdup(command));

	path_copy = strdup(path); /*create a copy of the PATH*/
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":"); /* divide PATH in array*/

	while (token)
	{
		/*Len of the path + command + '/' + '\0'*/
		len = strlen(token) + strlen(command) + 2;
		full_path = malloc(sizeof(char) * len);

		if (!full_path)
			break;
		/*Concatenate both to create the full path*/
		sprintf(full_path, "%s/%s", token, command);

		if (access(full_path, X_OK) == 0) /* check if full_path can be executed */
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);

		token = strtok(NULL, ":");
	}
	free(path_copy);
	free(token);

return (NULL);
}
