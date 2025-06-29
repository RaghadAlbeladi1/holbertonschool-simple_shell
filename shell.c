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
char     *command;
char    **args;
int       status = 1;

while (status)
{
print_prompt();
command = read_command();
if (!command)
{
putchar('\n');
break;
}
args   = split_command(command);
status = run_command(args);
free(command);
free(args);
}
}
