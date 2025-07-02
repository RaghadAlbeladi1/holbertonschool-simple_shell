#include "shell.h"

/* Static helper function */
static void handle_eof(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "\n", 1);
}

/* Main shell loop */
void shell_loop(void)
{
    char *line = NULL;
    char **args = NULL;
    int status = 1;

    while (status)
    {
        if (isatty(STDIN_FILENO))
            print_prompt();

        line = read_line();
        if (!line)
        {
            handle_eof();
            break;
        }

        args = parse_line(line);
        if (!args)
        {
            free(line);
            line = NULL;  // إضافة مهمة
            continue;
        }

        status = execute(args);

        /* التعديل الرئيسي هنا */
        if (status != -1)  // إذا لم تكن execute قد حررت الذاكرة
        {
            free_args(args);
            free(line);
        }

        args = NULL;  // إعادة التعيين مهمة
        line = NULL;
    }
}
