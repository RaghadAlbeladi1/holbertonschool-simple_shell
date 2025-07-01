#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFSIZE 64
#define DELIM " \t\n"

extern char **environ;

/* Function prototypes */
int execute(char **args);
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
void print_prompt(void);

#endif /* SHELL_H */
