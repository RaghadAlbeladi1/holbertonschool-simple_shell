#include "shell.h"

/**
 * main - Entry point for the shell
 * @argc: argument count (unused)
 * @argv: argument vector (unused)
 * @env: environment variables
 *
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
 char *line;
 char **args;

 (void)argc;
 (void)argv;

 while (1)
 {
  display_prompt();
  line = get_input();

  if (line == NULL)
  {
   write(STDOUT_FILENO, "\n", 1);
   break;
  }

  args = tokenize_input(line);

  if (args[0] != NULL)
  {
   if (!handle_builtins(args, env))
    execute_command(args, env);
  }

  free(args);
  free(line);
 }
 return (0);
}
