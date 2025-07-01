#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

#define BUFSIZE 64
#define DELIM " \t\n"

extern char **environ;

/* Main Functions */
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
void print_prompt(void);
int execute_command(char **args);

/* Command Execution */
int execute_external(char **args, char **env);
char *find_path(char *command, char **env);

/* Built-in Commands */
int shell_exit(char **args, char **env);
int shell_env(char **args, char **env);
int shell_cd(char **args, char **env);

/* Helper Functions */
int _strcmp(const char *s1, const char *s2);
int _atoi(char *s);
void free_tokens(char **tokens);
void _puts(char *str);

#endif /* SHELL_H */
