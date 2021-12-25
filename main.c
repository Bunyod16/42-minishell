/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:29:32 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/12/25 15:15:36 by hbaddrul         ###   ########.fr       */
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

static void	init_info(t_shell_info *info, char **envp)
{
	int		i;
	char	*prompt;

	info->envp = envp;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "USER=", 5))
			info->user = envp[i] + 5;
		else if (!ft_strncmp(envp[i], "PWD=", 4))
			info->pwd = ft_strrchr(envp[i], '/') + 1;
		else if (!ft_strncmp(envp[i], "PATH=", 5))
			info->paths = ft_split(ft_strchr(envp[i], '/'), ':');
	}
	info->envp_len = i;
	prompt = malloc(sizeof(char) * (ft_strlen(info->user) \
			+ ft_strlen(info->pwd) + 16));
	if (!prompt)
		return ;
	ft_strlcat(prompt, info->user, ft_strlen(info->user) + 1);
	ft_strlcat(prompt, "@minishell ", ft_strlen(prompt) + 11 + 1);
	ft_strlcat(prompt, info->pwd, ft_strlen(prompt) + ft_strlen(info->pwd) + 1);
	ft_strlcat(prompt, " $> ", ft_strlen(prompt) + 5 + 1);
	info->prompt = prompt;
}

static void	action(int sig)
{
	if (sig == SIGINT)
		ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	process_line(char *line, t_shell_info *info)
{
	char	**args;
	int		status;

	args = ft_split(line, ' ');
	status = 1;
	if (fork() == 0)
	{
		if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
			status = run_binary("echo", args, info);
		exit(0);
	}
	if (!status)
		printf("oops, something went wrong!\n");
	wait(0);
	return (1);
}

static void	eof(void)
{
	ft_putendl_fd("\nSaving session...", 1);
	ft_putendl_fd("...copying shared history...", 1);
	ft_putendl_fd("...saving history...truncating history files...", 1);
	ft_putendl_fd("...completed.\n", 1);
	ft_putendl_fd("[Process completed]", 1);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_shell_info	info;

	(void)argv;
	(void)envp;
	if (argc != 1)
		return (1);
	init_info(&info, envp);
	signal(SIGINT, action);
	signal(SIGQUIT, action);
	while (1)
	{
		line = readline(info.prompt);
		if (!line || (ft_strlen(line) == 4 && !ft_strncmp(line, "exit", 4)))
			break ;
		process_line(line, &info);
		add_history(line);
		free(line);
	}
	eof();
	return (0);
}
