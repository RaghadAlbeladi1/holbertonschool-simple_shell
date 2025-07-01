#include "shell.h"
#include <sys/stat.h>
#include <sys/wait.h>

/* دالة مقارنة النصوص (بدون استخدام strcmp من string.h) */
static int custom_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

/**
 * execute_command - تنفيذ الأوامر (بديل آمن لـ execute)
 * @args: مصفوفة الأوامر والوسائط
 * Return: 1 لمواصلة التنفيذ، 0 للخروج
 */
int execute_command(char **args)
{
    pid_t pid;
    int status;
    struct stat st;

    if (args[0] == NULL)
        return (1);

    /* معالجة الأوامر المدمجة */
    if (custom_strcmp(args[0], "exit") == 0)
        return (0);

    if (custom_strcmp(args[0], "env") == 0)
    {
        char **env = environ;
        while (*env)
            printf("%s\n", *env++);
        return (1);
    }

    /* التحقق من وجود الملف */
    if (stat(args[0], &st) == -1)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        return (1);
    }

    /* التحقق من صلاحيات التنفيذ */
    if (!(st.st_mode & S_IXUSR))
    {
        fprintf(stderr, "./hsh: 1: %s: Permission denied\n", args[0]);
        return (1);
    }

    /* إنشاء عملية جديدة */
    pid = fork();
    if (pid == 0)
    {
        /* عملية الابن */
        if (execve(args[0], args, environ) == -1)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* خطأ في fork */
        perror("./hsh");
    }
    else
    {
        /* عملية الأب */
        waitpid(pid, &status, WUNTRACED);
    }

    return (1);
}
