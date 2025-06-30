
#include "shell.h"

/**
 * execute_command - creates a child process and executes the command
 * @args: array of arguments
 * @env: environment variables
 */
void execute_command(char **args, char **env)
{
 pid_t pid;
 int status;

 pid = fork();
 if (pid == -1)
 {
  perror("fork failed");
  return;
 }

 if (pid == 0)
 {
  if (execve(args[0], args, env) == -1)
  {
   perror("execve failed");
   exit(EXIT_FAILURE);
  }
 }
 else
 {
  waitpid(pid, &status, 0);
 }
}
