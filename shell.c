#include "shell.h"

/* الدالة المساعدة */
static void handle_eof(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "\n", 1);
}

/* حلقة الشل الرئيسية */
void shell_loop(void)
{
    char *line = NULL;
    char **args = NULL;
    int status = 1;

    while (status)
    {
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
            continue;
        }

        status = execute(args);
        free(args);
        free(line);
    }
}

/* نقطة البداية */
int main(void)
{
    shell_loop();
    return 0;
}
