#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHELL_RL_BUFSIZE 1024
#define SHELL_TOK_DELIM  " \t\r\n"


extern char **environ;

/**
 * print_prompt - Prints the shell prompt.
 */
void print_prompt(void);

/**
 * shell_loop - Main loop executing the shell until EOF.
 */
void shell_loop(void);

/**
 * read_command - Reads a line of input from stdin.
 *
 * Return: Pointer to the command string, or NULL on EOF.
 */
char *read_command(void);

/**
 * split_command - Splits a command into tokens.
 * @command: The command string.
 *
 * Return: NULL‑terminated array of tokens.
 */
char **split_command(char *command);

/**
 * run_command - Forks and executes a command.
 * @args: NULL‑terminated array of arguments.
 *
 * Return: Exit status of the executed command.
 */
int run_command(char **args);
int handle_builtins(char **args, char **env);

int builtin_env(char **args);
int builtin_exit(char **args);
int handle_builtins(char **args, char **env);
#endif 
