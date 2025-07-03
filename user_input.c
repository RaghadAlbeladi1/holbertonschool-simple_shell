#include "shell.h"

/**
 * read_command - Reads a command from stdin
 * @command: Buffer to store command
 * @size: Size of buffer
 *
 * Return: 0 on success, -1 on failure
 */
int read_command(char *command, size_t size)
{
    ssize_t read;

    read = getline(&command, &size, stdin);
    if (read == -1)
    {
        if (feof(stdin))
        {
            print_message("\n");
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("read_command");
            return (-1);
        }
    }

    command[read - 1] = '\0'; /* Remove newline */
    return (0);
}
