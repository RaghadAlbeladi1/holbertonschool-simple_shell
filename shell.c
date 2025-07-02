#include "shell.h"

/* الدوال المساعدة */
static void handle_eof(void) {
    /* ... */
}

/* دالة shell_loop الرئيسية */
void shell_loop(void) {
    char *line = NULL;
    char **args = NULL;
    int status = 1;

    while (status) {
        /* طباعة موجه الأوامر في الوضع التفاعلي */
        if (isatty(STDIN_FILENO))
            print_prompt();

        /* قراءة الإدخال */
        line = read_line();
        if (!line) {
            handle_eof();
            break;
        }

        /* تحليل الإدخال إلى وسائط */
        args = parse_line(line);
        if (!args) {
            free(line);
            continue;
        }

        /* تنفيذ الأمر */
        status = execute(args);

        /* تحرير الذاكرة */
        if (status != -1) {  // إذا لم يكن أمرًا مدمجًا
            free_args(args);
            free(line);
        }
        args = NULL;
        line = NULL;
    }
}

/* نقطة الدخول الرئيسية */
int main(void) {
    shell_loop();  // <-- هنا يتم استدعاء shell_loop
    return 0;
}
