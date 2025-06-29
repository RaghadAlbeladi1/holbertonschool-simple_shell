#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHELL_RL_BUFSIZE 1024
#define SHELL_TOK_DELIM  " \t\r\n"

extern char **environ;

void print_prompt(void);
void shell_loop(void);
char *read_command(void);
char **split_command(char *command);
int run_command(char **args);
int handle_builtins(char **args, char **env);

#endif /* SHELL_H */
