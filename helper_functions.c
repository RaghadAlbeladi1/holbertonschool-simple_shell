#include "shell.h"
#include <stdlib.h>
#include <string.h>

/* Add this extern declaration for environ */
extern char **environ;

/**
 * _getpath - Gets the PATH environment variable
 * Return: PATH string or NULL
 */
char *_getpath(void)
{
    char **env = environ;
    char *path = NULL;

    while (*env)
    {
        if (strncmp(*env, "PATH=", 5) == 0)
        {
            path = *env + 5;
            break;
        }
        env++;
    }
    return path;
}
