#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * handle_builtins - Handles built-in shell commands
 * @args: Array of command arguments
 * Return: 1 if built-in handled, 0 otherwise
 */
int handle_builtins(char **args)
{
    if (!args[0])
        return 0;

    if (strcmp(args[0], "exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(args[0], "echo") == 0)
    {
        int i = 1;
        while (args[i])
        {
            printf("%s", args[i]);
            if (args[i+1])
                printf(" ");
            i++;
        }
        printf("\n");
        return 1;
    }
    return 0;
}

/**
 * free_args - Frees memory allocated for arguments
 * @args: Array of arguments to free
 */
void free_args(char **args)
{
    if (!args)
        return;

    int i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}
