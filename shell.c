#include "shell.h"

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always EXIT_SUCCESS.
 */
int main(void)
{
shell_loop();
return (EXIT_SUCCESS);
}

/**
 * shell_loop - Reads and executes commands until EOF.
 */
void shell_loop(void)
{
char *command = NULL;
char **args = NULL;
int status = 1;
while (status)
{
print_prompt();
command = read_command();
if (!command) /* Ctrl+D */
{
putchar('\n');
break;
}
if (command[0] == '\0')
{
free(command);
continue;
}
args = split_command(command);
status = run_command(args);

free(command);
free(args);
}
}
