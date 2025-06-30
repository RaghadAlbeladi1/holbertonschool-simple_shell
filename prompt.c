#include "shell.h"

/**
 * print_prompt - Prints shell prompt
 */
void print_prompt(void)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "#cisfun$ ", 9);
}
