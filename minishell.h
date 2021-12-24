#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_shell_info
{
    char    **envp;
}   t_shell_info;

int echo_test(char *line, t_shell_info *info);

#endif 