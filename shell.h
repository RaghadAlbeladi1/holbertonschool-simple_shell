#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 128

/* Function prototypes */
void display_prompt(void);
void print_message(const char *msg);
int read_command(char *command, size_t size);
int execute_command(const char *command);
int handle_builtin(char *command);

#endif /* SHELL_H */
