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

 * hsh_execute - Fork process and replace the child with a new program
 * @arguments: String of arguments (tokens)
 * @argv: Array of arguments
 * @exit_status: Exit status
 * Return: Always 1 (success).

 * execute - Executes a command
 * @args: Command and arguments
 * Return: 1 to continue, 0 to exit

 */
int hsh_execute(char **arguments, char **argv, int *exit_status)
{
	pid_t pid;

	int status;
	char *new_arguments;


	new_arguments = validate_input(arguments, argv);
	if (strcmp(new_arguments, "Fail access") == 0)
		return (1);

	pid = fork();
	if (pid == 0)
	{

		if (execve(new_arguments, arguments, environ) == -1)
		{
			perror("execve fail");

			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Error forking");
		free(new_arguments);
		return (1);
	}
	else
	{

		waitpid(-1, &status, 0);

		if (WIFEXITED(status))

			*exit_status = WEXITSTATUS(status);

		if (arguments[0][0] != '/' && arguments[0][0] != '.')
			free(new_arguments);
		return (1);
	}
	return (1);
}

/**
 * hsh_execute_builtins - Choose from an array of builtin functions
 * @args: String of arguments (tokens)
 * @input_stdin: String from input
 * @argv: Array of arguments
 * @exit_status: Exit status
 * Return: Status to stay or exit the main loop, 1 or 0
 */
int hsh_execute_builtins(char **args, char *input_stdin,
			 char **argv, int *exit_status)
{
	int i = 0;


	choose_builtins_t options[] = {
		{"exit", hsh_exit},
		{"env", hsh_env},
		{"cd", hsh_cd},
		{"setenv", hsh_setenv},
		{"unsetenv", hsh_unsetenv},
		{NULL, NULL}
	};

	while (options[i].name_builtin)
	{

		if (strcmp(options[i].name_builtin, args[0]) == 0)
		{

			return ((int)((*options[i].func_builtin)(args, input_stdin, exit_status)));
		}
		i++;
	}

	return (hsh_execute(args, argv, exit_status));

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
