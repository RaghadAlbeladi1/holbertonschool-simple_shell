#include <unistd.h>
#include <stdio.h>
#include "shell.h"

/**
* handle_cd - Handles the built-in 'cd' command
* @args: Array of command arguments
*/
void handle_cd(char **args)
{
if (args[1] == NULL)
{
fprintf(stderr, "cd: expected argument\n");
}
else
{
if (chdir(args[1]) != 0)
{
perror("cd");
}
}
}
