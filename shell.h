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
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
/* prototype */
extern char **environ;
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
void print_prompt(void);
int handle_builtins(char **args);
void handle_cd(char **args);
void handle_exit(char **args);
void handle_env(char **args);
void free_array(char **arr);
void free_resources(void);
char *find_in_path(char *cmd);
char *_getpath(void);
void handle_signal(int sig);
void print_error(char *msg, char *detail);

#endif /* SHELL_H */
