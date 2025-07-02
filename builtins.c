#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * handle_builtins - Execute built-in shell commands
 * @args: Argument array
 * Return: 1 if built-in handled, 0 otherwise
 */
int handle_builtins(char **args)
{
    if (!args || !args[0])
        return 0;

    if (strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(args[0], "echo") == 0) {
        int i = 1;
        while (args[i]) {
            printf("%s", args[i]);
            if (args[++i]) printf(" ");
        }
        printf("\n");
        return 1;
    }
    return 0;
}

/**
 * free_args - Free argument array memory
 * @args: Argument array to free
 */
void free_args(char **args)
{
    if (!args) return;
    
    int i = 0;
    while (args[i]) free(args[i++]);
    free(args);
}
