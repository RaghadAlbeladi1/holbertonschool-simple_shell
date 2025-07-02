#include <unistd.h>
#include <string.h>

/**
 * print_message - Prints a message to stdout, optionally with newline
 * @msg: Message to print
 * @newline: If non-zero, print a newline after the message
 */
void print_message(const char *msg, int newline)
{
    write(STDOUT_FILENO, msg, strlen(msg));
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
}

