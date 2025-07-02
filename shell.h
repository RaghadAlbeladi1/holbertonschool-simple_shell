#ifndef SHELL_H
#define SHELL_H

/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

/* Function prototypes */
void display_prompt(void);
void print_message(const char *message);
void read_command(char *command, size_t size);
int execute_command(const char *command);
int handle_builtin(char *command);

#endif /* SHELL_H */

