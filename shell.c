#include "shell.h"

/* Static helper functions (file-scoped) */
static void handle_eof(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "\n", 1);
}

/* Rest of your implementation */
void shell_loop(void)
{
    /* ... */
    if (!line) {
        handle_eof();  // Now properly defined before use
        break;
    }
    /* ... */
}
