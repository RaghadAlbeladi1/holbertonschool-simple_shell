#include "shell.h"

/**
* free_resources - Frees all allocated resources
*
* Description: Frees any memory allocated by the shell that needs
*              to be cleaned up before exit.
*/
void free_resources(void)
{
/* Example - add your actual allocations here */
extern char *input_buffer;
extern char **command_args;

if (input_buffer != NULL)
{
free(input_buffer);
input_buffer = NULL;
}

if (command_args != NULL)
{
free(command_args);
command_args = NULL;
}
}
