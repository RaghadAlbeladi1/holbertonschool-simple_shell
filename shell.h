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

/* Core Shell Functions */
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
void print_prompt(void);

/* Command Execution */
int execute(char **args, char **env);            // الرئيسية
int execute_external(char **args, char **env);   // للأوامر الخارجية
char *find_path(char *command, char **env);     // للبحث في PATH

/* Built-in Commands */
int shell_exit(char **args, char **env);        // للأمر exit
int shell_env(char **args, char **env);         // للأمر env
int shell_cd(char **args, char **env);          // للأمر cd

/* Helper Functions */
int _strcmp(const char *s1, const char *s2);    // مقارنة سلاسل
int _strncmp(const char *s1, const char *s2, size_t n); // مقارنة n أحرف
int _atoi(char *s);                             // تحويل سلسلة إلى عدد
void free_tokens(char **tokens);                // تحرير الذاكرة
void _puts(char *str);                          // طباعة سلسلة

#endif /* SHELL_H */
