#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define BUFSIZE 64
#define DELIM_I " \t\n"
#define DELIM_P ":"

/**
 * struct choose_builtin - Builtin commands struct
 * @name_builtin: Name of builtin command
 * @func_builtin: Pointer to builtin command functions
 */
typedef struct choose_builtin
{
	char *name_builtin;
	int (*func_builtin)(char **, char *, int *);

} choose_builtins_t;


extern char **environ;

int main(int argc __attribute__((unused)),
	 char **argv __attribute__((unused)));
char **hsh_tokenizer(char *input);
char **tokenizer_path(char *input);
char *validate_input(char **arguments, char **argv);
int validate_spaces(char *input);
int hsh_execute(char **arguments, char **argv, int *exit_status);
int hsh_execute_builtins(char **args, char *input_stdin,
			 char **argv, int *exit_status);
int hsh_cd(char **args, char *input_stdin, int *exit_status);
int hsh_setenv(char **args,  char *input_stdin, int *exit_status);
int hsh_unsetenv(char **args,  char *input_stdin, int *exit_status);
int hsh_env(char **args, char *input_stdin, int *exit_status);
int hsh_exit(char **args, char *input_stdin, int *exit_status);
void sigintH(int signum);
char *str_concat(char *s1, char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif /* SHELL_H */
