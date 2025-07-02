#include "shell.h"
#include <string.h>

int handle_builtins(char **args)
{
    int i;

    if (!args[0])
        return 0;

    if (strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(args[0], "echo") == 0) {
        i = 1;
        while (args[i]) {
            printf("%s", args[i]);
            if (args[i+1]) printf(" ");
            i++;
        }
        printf("\n");
        return 1;
    }
    return 0;
}

void free_args(char **args)
{
    int i = 0;

    if (!args) return;

    while (args[i]) {
        free(args[i]);
        i++;
    }
    free(args);
}
