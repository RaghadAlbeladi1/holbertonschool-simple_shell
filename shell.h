#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define BUFSIZE 64
#define DELIM " \t\n"

extern char **environ;

/* Function prototypes */
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
void print_prompt(void);

int shell_exit(void);
int shell_env(void);


#endif /* SHELL_H */

