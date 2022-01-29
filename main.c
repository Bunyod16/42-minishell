/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:29:32 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/29 21:49:50 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "libft/libft.h"
#include "libreadline/history.h"
#include "libreadline/readline.h"

static void	action(int sig)
{
	if (sig == SIGINT)
		ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	update_prompt(t_shell_info *info)
{
	char	*buf;
	char	*pwd;
	char	*user;
	char	*prompt;
	size_t	size;

	buf = 0;
	size = 0;
	pwd = getcwd(buf, size);
	user = get_env(&info->env, "USER");
	prompt = ft_strdup(user);
	add_substr(&prompt, ft_strlen(prompt), "@minishell ");
	add_substr(&prompt, ft_strlen(prompt), ft_strrchr(pwd, '/') + 1);
	free(pwd);
	add_substr(&prompt, ft_strlen(prompt), " $> ");
	info->prompt = prompt;
}

static void	executor(t_shell_info *info) // redirections etc
{
	int			status;
	pid_t		pid;
	t_cmd_list	*cmd_lst;

	cmd_lst = info->cmd_lst;
	while (cmd_lst)
	{
		pid = fork();
		if (pid == -1)
			perror("fork error");
		else if (!pid)
		{
			execve(cmd_lst->cmds[0], cmd_lst->cmds, info->envp);
			perror("execve error");
		}
		cmd_lst = cmd_lst->next;
	}
	if (waitpid(pid, &status, 0) == -1)
		perror("waitpid error");
}

int	main(int argc, char **argv, char **envp)
{
	int				i;
	char			*line;
	t_list			*token_lst;
	t_shell_info	info;

	(void)argv;
	if (argc != 1)
		return (1);
	if (signal(SIGINT, action) == SIG_ERR || signal(SIGQUIT, action) == SIG_ERR)
		perror("signal error");
	info.env = init_env(envp);
	info.envp = set_envp(&info.env);
	while (1)
	{
		update_prompt(&info);
		line = readline(info.prompt);
		free(info.prompt);
		if (!line || (ft_strlen(line) == 4 && !ft_strncmp(line, "exit", 4)))
			break ;
		if (!ft_strlen(line))
			continue ;
		quoter(&line);
		piper(&line);
		if (!line)
		{
			ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
			continue ;
		}
		add_history(line);
		spacer(&line);
		token_lst = lexer(line); // TODO: expand environment variables
		if (!is_syntax_cmd(token_lst))
			continue ;
		info.cmd_lst = parser(token_lst); // TODO: parse into t_cmd_list
		ft_lstclear(&token_lst, free);
		executor(&info); // TODO: handle builtins
		free(line);
	}
	env_clear(&info.env, free);
	i = 0;
	while (info.envp[i])
		free(info.envp[i++]);
	free(info.envp);
	rl_clear_history();
	ft_putendl_fd("exit", 1);
	return (0);
}
