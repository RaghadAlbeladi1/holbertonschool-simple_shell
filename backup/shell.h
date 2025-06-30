#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define BUFSIZE 1024
#define DELIM " \t\n"

extern char **environ;

/* Function prototypes */
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
void print_prompt(void);
int launch(char **args);

/* Built-in functions */
int shell_exit(char **args);
int shell_env(char **args);

#endif
