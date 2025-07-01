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

  
int shell_exit(void);
int shell_env(void);
void handle_cd(char **args);
char *find_command(char *cmd);
int execute_command(char **args, char **env);

\\

#endif /* SHELL_H */

