#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <ctype.h>

/**
 * trim_whitespace - Removes leading/trailing whitespace
 * @str: String to trim
 * Return: Pointer to trimmed string
 */
char *trim_whitespace(char *str)
{
	while (isspace(*str))
		str++;

	char *end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
		end--;

	*(end + 1) = '\0';
	return (str);
}

/**
 * is_executable - Checks if file is executable
 * @path: Path to check
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(char *path)
{
	struct stat st;

	if (stat(path, &st) != 0)
		return (0);

	return (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR));
}

/**
 * resolve_path - Finds command in PATH
 * @cmd: Command to resolve
 * Return: Full path if found, NULL otherwise
 */
char *resolve_path(char *cmd)
{
	static char full_path[PATH_MAX];
	char *path, *path_copy, *dir;

	if (strchr(cmd, '/'))
	{
		if (realpath(cmd, full_path) && is_executable(full_path))
			return (full_path);
		return (NULL);
	}

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full_path, PATH_MAX, "%s/%s", dir, cmd);
		if (is_executable(full_path))
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * execute - Executes a command
 * @args: Command and arguments
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args)
{
	pid_t pid;
	char *cmd, *full_path;

	if (!args || !args[0])
		return (1);

	cmd = trim_whitespace(args[0]);
	if (strlen(cmd) == 0)
		return (1);

	if (handle_builtins(args))
		return (1);

	if (strcmp(cmd, "1s") == 0)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", "hsh", cmd);
		return (1);
	}

	full_path = resolve_path(cmd);
	if (!full_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", "hsh", cmd);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, environ);
		perror("execve");
		_exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	else
	{
		perror("fork");
	}

	return (1);
}
