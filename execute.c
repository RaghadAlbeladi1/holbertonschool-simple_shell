#include "shell.h"

/**
 * is_builtin - Checks and executes built-in commands
 * @args: Command and arguments
 *
 * Return: 1 if a built-in command was executed, 0 otherwise
 */
int is_builtin(char **args)
{
 int i = 0;

 if (strcmp(args[0], "env") == 0)
 {
  while (environ[i])
  {
   printf("%s\n", environ[i]);
   i++;
  }
  return (1);
 }
 else if (strcmp(args[0], "cd") == 0)
 {
  handle_cd(args);
  return (1);
 }

 return (0);
}

/**
 * resolve_cmd_path - Resolves the full path of the command
 * @cmd: Command name
 *
 * Return: Pointer to command path if found, NULL otherwise
 */
char *resolve_cmd_path(char *cmd)
{
 char *cmd_path = NULL;

 if (strchr(cmd, '/'))
 {
  if (access(cmd, X_OK) == 0)
   cmd_path = strdup(cmd);
 }
 else
 {
  cmd_path = find_command(cmd);
 }

 return (cmd_path);
}

/**
 * run_cmd - Forks and executes the command
 * @cmd_path: Path to the executable command
 * @args: Command and arguments
 *
 * Return: Exit status of the command
 */
int run_cmd(char *cmd_path, char **args)
{
 pid_t pid;
 int status;

 pid = fork();
 if (pid == 0)
 {
  if (execve(cmd_path, args, environ) == -1)
  {
   fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
   free(cmd_path);
   exit(127);
  }
 }
 else if (pid < 0)
 {
  perror("fork");
  status = 1;
 }
 else
 {
  waitpid(pid, &status, 0);
  if (WIFEXITED(status))
   status = WEXITSTATUS(status);
  else
   status = 1;
 }

 return (status);
}

/**
 * execute_cmd - Main command execution handler
 * @args: Command and arguments
 *
 * Return: Exit status
 */
int execute_cmd(char **args)
{
 char *cmd_path;
 int status;

 if (args[0] == NULL)
  return (0);

 if (is_builtin(args))
  return (0);

 cmd_path = resolve_cmd_path(args[0]);
 if (cmd_path == NULL)
 {
  fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
  return (127);
 }

 status = run_cmd(cmd_path, args);
 free(cmd_path);

 return (status);
}
