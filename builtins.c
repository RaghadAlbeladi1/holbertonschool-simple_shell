#include "shell.h"
#include <string.h>

/**
 * handle_builtins - Handle built-in commands
 * @args: Array of arguments
 * Return: 1 if built-in found and memory should NOT be freed, 0 otherwise
 */
int handle_builtins(char **args)
{
    int i;

    if (strcmp(args[0], "exit") == 0)
    {
        printf("Exiting shell...\n");  // رسالة تأكيد
        exit(EXIT_SUCCESS);  // لا تحرير الذاكرة هنا
    }
    else if (strcmp(args[0], "echo") == 0)
    {
        for (i = 1; args[i] != NULL; i++)
        {
            printf("%s", args[i]);
            if (args[i+1] != NULL)
                printf(" ");
        }
        printf("\n");
        return 1;  // إشارة أن الذاكرة يجب عدم تحريرها
    }
    return 0;
}

/**
 * free_args - Free memory allocated for arguments
 * @args: Array of arguments to free
 */
void free_args(char **args)
{
    int i;

    if (args == NULL)
        return;

    for (i = 0; args[i] != NULL; i++) {
        free(args[i]);
        args[i] = NULL;  // إضافة مهمة للسلامة
    }
    free(args);
}
