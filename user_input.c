#include "shell.h"

/**
 * read_line - Reads a line from stdin
 * Return: Pointer to the line
 */
char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    nread = getline(&line, &len, stdin);
    if (nread == -1)
    {
        free(line);
        return NULL;
    }

    /* Remove trailing newline */
    if (line[nread - 1] == '\n')
        line[nread - 1] = '\0';

    return line;
}

/**
 * parse_line - Parses a line into arguments
 * @line: Line to parse
 * Return: Array of arguments
 */
char **parse_line(char *line)
{
    int bufsize = BUFSIZE, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIM);
    while (token)
    {
        tokens[pos++] = token;
        if (pos >= bufsize)
        {
            bufsize += BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, DELIM);
    }
    tokens[pos] = NULL;
    return tokens;
}
