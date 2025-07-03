#include "shell.h"
#include <unistd.h>

/**
 * print_message - Prints a message to stdout
 * @msg: Message to print
 */
void print_message(const char *msg)
{
    if (msg)
        write(STDOUT_FILENO, msg, strlen(msg));
}
