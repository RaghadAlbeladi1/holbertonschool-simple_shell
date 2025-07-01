#include "shell.h"

/**
 * print_prompt - Displays the shell prompt.
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
