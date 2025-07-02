#include "shell.h"

void print_message(const char *message) {
    write(STDOUT_FILENO, message, strlen(message));
}
