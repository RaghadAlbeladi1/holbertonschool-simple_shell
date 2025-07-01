#ifndef SHELL_H
#define SHELL_H

/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

/* Constants */
#define BUFSIZE 1024
#define DELIM " \t\n"

/* Global Variables */
extern char **environ;

/* Function Prototypes */
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
void print_prompt(void);
int launch(char **args);
int shell_exit(char **args);
int shell_env(char **args);

#endif /* SHELL_H */
