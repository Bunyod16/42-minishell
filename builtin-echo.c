#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static int call_echo(t_shell_info *info)
{
    char *argv[2];

    argv[0] = "hello";
    argv[1] = 0;
    execve("echo", argv, info->envp);
    return (1);
}

int echo_test(char *line, t_shell_info *info)
{
    int pid;

    printf("%s\n",line);
    pid = fork();
    if (pid == -1)
        call_echo(info);
    return (1);
}