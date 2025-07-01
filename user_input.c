#include "shell.h"

char **parse_line(char *line) {
    int bufsize = BUFSIZE, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    if (!tokens) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line, DELIM);
    while (token) {
        tokens[pos++] = token;

        if (pos >= bufsize) {
            bufsize += BUFSIZE;
            char **new_tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!new_tokens) {
                perror("realloc");
                free(tokens);
                exit(EXIT_FAILURE);
            }
            tokens = new_tokens;
        }

        token = strtok(NULL, DELIM);
    }
    tokens[pos] = NULL;
    return tokens;
}
