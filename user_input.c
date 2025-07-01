#include "shell.h"

/**
 * parse_line - Splits a string into tokens (must be freed by caller)
 * @line: The input string to split
 * Return: Array of tokens, or NULL on failure
 */
char **parse_line(char *line)
{
    if (!line || !*line) {
        return NULL;
    }

    int bufsize = BUFSIZE, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    if (!tokens) {
        perror("malloc failed");
        return NULL;
    }

    char *token = strtok(line, DELIM);
    while (token) {
        tokens[pos++] = token;

        if (pos >= bufsize) {
            bufsize += BUFSIZE;
            char **new_tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!new_tokens) {
                perror("realloc failed");
                free(tokens);
                return NULL;
            }
            tokens = new_tokens;
        }

        token = strtok(NULL, DELIM);
    }
    tokens[pos] = NULL;
    return tokens;
}
