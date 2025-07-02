#include "shell.h"

/**
 * handle_builtins - Handle built-in commands
 * @args: Array of arguments
 * Return: 1 if built-in found, 0 otherwise
 */
int handle_builtins(char **args)
{
    if (strcmp(args[0], "exit") == 0)
    {
        free_args(args);
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(args[0], "echo") == 0)
    {
        for (int i = 1; args[i] != NULL; i++)
        {
            printf("%s", args[i]);
            if (args[i+1] != NULL)
                printf(" ");
        }
        printf("\n");
        return 1;
    }
    /* Add more built-ins here */

    return 0;
}

/**
 * free_args - Free memory allocated for arguments
 * @args: Array of arguments to free
 */
void free_args(char **args)
{
    if (args == NULL)
        return;

    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);

    free(args);
}
