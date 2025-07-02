#include "shell.h"

/**
* handle_builtins - Handles built-in commands
* @args: Command arguments
* Return: 1 if builtin handled, 0 otherwise
*/
int handle_builtins(char **args)
{
if (!args[0])
return 0;

if (strcmp(args[0], "exit") == 0)
{
exit(EXIT_SUCCESS);
}
else if (strcmp(args[0], "env") == 0)
{
char **env = environ;
while (*env)
{
printf("%s\n", *env);
env++;
}
return 1;
}

return 0;
}
