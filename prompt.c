#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 *
 * Description: Shows "$ " when in interactive mode.
 * Uses write() for exact control over output.
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
