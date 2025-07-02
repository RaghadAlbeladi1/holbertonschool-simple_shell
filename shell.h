#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 64
#define DELIM " \t\n"

/* Function prototypes */
int handle_builtins(char **args);
void free_args(char **args);
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
void print_prompt(void);
/* Environment variable handling */
extern char **environ;
char *_getpath(void);
char *find_in_path(char *cmd);
#endif
