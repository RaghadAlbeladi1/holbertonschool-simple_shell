#include "shell.h"

/**
 * print_prompt - Displays shell prompt
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
