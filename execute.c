#include "shell.h"
#include <sys/wait.h>

/**
* find_command - Search for command in PATH environment variable
* @command: command name
* @env: environment variables
*
* Return: full path to command or NULL if not found
*/
char *find_command(char *command, char **env)
{
char *path_env = NULL, *path_dup, *token, *full_path;
int len;

for (int i = 0; env[i]; i++)
{
if (strncmp(env[i], "PATH=", 5) == 0)
{
path_env = env[i] + 5;
break;
}
}
if (!path_env)
return NULL;

path_dup = strdup(path_env);
token = strtok(path_dup, ":");
while (token)
{
len = strlen(token) + strlen(command) + 2;
full_path = malloc(len);
if (!full_path)
{
free(path_dup);
return NULL;
}
snprintf(full_path, len, "%s/%s", token, command);
if (access(full_path, X_OK) == 0)
{
free(path_dup);
return full_path;
}
free(full_path);
token = strtok(NULL, ":");
}
free(path_dup);
return NULL;
}

/**
* execute_command - execute command by forking and calling execve
* @args: command arguments
* @env: environment variables
*/
void execute_command(char **args, char **env)
{
pid_t pid;
int status;
char *cmd_path;

if (strchr(args[0], '/'))
cmd_path = args[0];
else
{
cmd_path = find_command(args[0], env);
if (!cmd_path)
{
perror("command not found");
return;
}
}

pid = fork();
if (pid == -1)
{
perror("fork failed");
if (cmd_path != args[0])
free(cmd_path);
return;
}

if (pid == 0)
{
if (execve(cmd_path, args, env) == -1)
{
perror("execve failed");
if (cmd_path != args[0])
free(cmd_path);
exit(EXIT_FAILURE);
}
}
else
waitpid(pid, &status, 0);

if (cmd_path != args[0])
free(cmd_path);
}

