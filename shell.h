#ifndef SHELL_H
#define SHELL_H

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

/* Function Prototypes */
void display_prompt(void);
char *get_input(void);
char **tokenize_input(char *line);
int shell_exit(void);
int shell_env(void);
void execute_command(char **args, char **env);
char *find_command(char *command, char **env);


/* Environment */
extern char **environ;

/* Function prototypes */
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
void print_prompt(void);

#endif /* SHELL_H */
