#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * read_line - Reads a line of input from stdin
 * Return: Pointer to the input string, or NULL on failure/EOF
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    /* Using getline for dynamic buffer allocation */
    nread = getline(&line, &bufsize, stdin);

    if (nread == -1)
    {
        free(line);  /* Free if getline fails */
        return NULL;
    }

    /* Remove trailing newline if present */
    if (nread > 0 && line[nread-1] == '\n')
        line[nread-1] = '\0';

    return line;
}
