#include "shell.h"

void print_mes(const char *message) {
    write(STDOUT_FILENO, message, strlen(message));
}
