#include "shell.h"

/**
 * execute_command - Executes a shell command using fork and execvp
 * @command: The command string to execute
 */
void execute_command(const char *command)
{
	pid_t child_pid;
	char *args[128];
	char command_copy[1024];
	int arg_count = 0;
	char *token;

	child_pid = fork();
	if (child_pid == -1)
	{
		print_message("Error forking process.\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		strncpy(command_copy, command, sizeof(command_copy) - 1);
		command_copy[sizeof(command_copy) - 1] = '\0';

		token = strtok(command_copy, " ");
		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		execvp(args[0], args);
		print_message("Error executing command.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

