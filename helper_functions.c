#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* READ */
char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    nread = getline(&line, &len, stdin);
    if (nread == -1) {
        free(line);
        return NULL;
    }
    return line;
}

/* READ */
char *_getpath(void)
{
    char **env = environ;
    while (*env) {
        if (strncmp(*env, "PATH=", 5) == 0)
            return (*env + 5);
        env++;
    }
    return NULL;
}
