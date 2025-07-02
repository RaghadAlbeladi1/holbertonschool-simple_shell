#include "shell.h"

/**
 * print_message - Prints a message to stdout
 * @message: The message to print
 */
void print_message(const char *message)
{
	if (message)
		write(STDOUT_FILENO, message, strlen(message));
}

