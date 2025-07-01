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

void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
void print_prompt(void);

int execute_command(char **args, char **env);
char *find_path(char *command, char **env);
int handle_builtins(char **args, char **env);
int shell_exit(char **args);
int shell_env(char **env);

int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *str);
void print_error(char *prog_name, char *cmd, char *msg);

#endif /* SHELL_H */
