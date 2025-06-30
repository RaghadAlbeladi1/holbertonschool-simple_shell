#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function Prototypes */
void display_prompt(void);
char *get_input(void);
char **tokenize_input(char *line);
int handle_builtins(char **args, char **env);
void execute_command(char **args, char **env);
char *find_command(char *command, char **env);

#endif /* SHELL_H */

