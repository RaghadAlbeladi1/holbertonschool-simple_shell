#include "shell.h"

char **parse_line(char *line)
{
    int bufsize = BUFSIZE, pos = 0;
    char **tokens, **new_tokens;
    char *token;

    if (!line || !*line)
        return NULL;

    tokens = malloc(bufsize * sizeof(char *));
    if (!tokens)
    {
        perror("malloc failed");
        return NULL;
    }

    token = strtok(line, DELIM);
    while (token)
    {
        tokens[pos++] = token;

        if (pos >= bufsize)
        {
            bufsize += BUFSIZE;
            new_tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!new_tokens)
            {
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
