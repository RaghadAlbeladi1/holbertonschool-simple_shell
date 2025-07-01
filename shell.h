#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define BUFSIZE 64
#define DELIM " \t\n"

typedef struct builtin
{
    char *name;
    int (*func)(char **args, char **env);
} builtin_t;

extern char **environ;

/* Core functions */
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);


int handle_builtin(char **args, char **env);
int shell_exit(char **args, char **env);
int shell_env(char **args, char **env);
int shell_cd(char **args, char **env);


int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *str);
char *find_path(char *command, char **env);
void print_error(char *msg);

#endif /* SHELL_H */
