#include "shell.h"

/**
 * prompt - check if input is from terminal, and display prompt
 */

void prompt(void)
{
	char cwd[BUFF_SIZE];

	if (isatty(STDIN_FILENO))
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL) /* get the Current Working Directory */
		{
			if (isatty(STDIN_FILENO)) /* check if we are in a terminal  */
			{
				write(STDOUT_FILENO, "HugoAdrien@", 11);
				write(STDOUT_FILENO, cwd, strlen(cwd));
				write(STDOUT_FILENO, "$ ", 2);
			}
		}
		else
			/* Default prompt if getcwd fails */
			write(STDOUT_FILENO, "HugoAdrien@shell$ ", 18);
	}
}
