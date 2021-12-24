#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_shell_info
{
    char **envp;
    char **paths;
} t_shell_info;

int         run_binary(char *binary, char **args, t_shell_info *info);

#endif