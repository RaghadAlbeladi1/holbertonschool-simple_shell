#include "shell.h"

/**
 * handle_sigint - hanfle the SIGINT signal (CTRL C)
 * @signal: unsused here
 */

void handle_sigint(int signal)
{
	char cwd[BUFF_SIZE];

	signal = signal; /* Signal unused here */

	write(STDOUT_FILENO, "\n", 1);

	if (getcwd(cwd, sizeof(cwd)) != NULL) /* get the Current Working Directory */
	{
		write(STDOUT_FILENO, "HugoAdrien@", 11);
		write(STDOUT_FILENO, cwd, strlen(cwd));
		write(STDOUT_FILENO, "$ ", 2);
	}
	else
		/* Default prompt if getcwd fails */
		write(STDOUT_FILENO, "HugoAdrien@shell$ ", 19);
}
