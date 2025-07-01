#include "shell.h"
#include <string.h>

/**
 * execute - Checks and executes built-in or external commands.
 * @args: Array of parsed arguments.
 *
 * Return: 1 to continue running the shell, or other status from built-in.
 */
int execute(char **args)
{
int status;
unsigned int i;

built_s builtins[] = {
{"exit", shell_exit},
{"env", shell_env},
{NULL, NULL}
};

if (args[0] == NULL)
return (1);

for (i = 0; builtins[i].name != NULL; i++)
{
if (strcmp(args[0], builtins[i].name) == 0)
{
status = builtins[i].func();
return (status);
}
}

return (execute_external(args));
}

/**
 * execute_external - Executes non-built-in (external) commands.
 * @args: Array of command and its arguments.
 *
 * Return: 1 to continue running the shell.
 */
int execute_external(char **args)
{
pid_t pid;
int status;

if (args[0] == NULL)
return (1);

pid = fork();
if (pid == 0)
{
if (execve(args[0], args, environ) == -1)
{
perror("hsh");
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{
perror("fork");
}
else
{
waitpid(pid, &status, 0);
}

return (1);
}
