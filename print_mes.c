#include "shell.h"
#include <unistd.h>
#include <string.h>

/**
 * print_message - Prints a message to stdout with newline control
 * @msg: Message to print
 * @newline: Flag to add newline (1 = yes, 0 = no)
 *
 * Return: Number of bytes written, -1 on error
 */
ssize_t print_message(const char *msg, int newline)
{
    ssize_t bytes = 0, ret;

    if (!msg)
        return (0);

    ret = write(STDOUT_FILENO, msg, strlen(msg));
    if (ret == -1)
        return (-1);
    bytes += ret;

    if (newline)
    {
        ret = write(STDOUT_FILENO, "\n", 1);
        if (ret == -1)
            return (-1);
        bytes += ret;
    }

    return (bytes);
}
