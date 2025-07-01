#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/**
 * find_command - Searches PATH for the given command
 * @cmd: The command name
 * Return: Full path to the command, or NULL if not found
 */
char *find_command(char *cmd)
{
char *path = getenv("PATH");
char *path_copy = strdup(path);
char *token = strtok(path_copy, ":");
static char full_path[1024];

while (token != NULL)
{
snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
if (access(full_path, X_OK) == 0)
{
free(path_copy);
return full_path;
}
token = strtok(NULL, ":");
}

free(path_copy);
return NULL;
}
