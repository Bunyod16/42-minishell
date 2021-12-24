/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:29:32 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/12/25 03:22:55 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "libreadline/history.h"
#include "libreadline/readline.h"
#include "minishell.h"
#include <sys/wait.h>

static void	action(int sig)
{
	if (sig == SIGINT)
		return ;
}

static void	eof(void)
{
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("Saving session...", 1);
	ft_putendl_fd("...copying shared history...", 1);
	ft_putendl_fd("...saving history...truncating history files...", 1);
	ft_putendl_fd("...completed.", 1);
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("[Process completed]", 1);
}

static void init_info(t_shell_info *info, char **envp)
{
	int	i;

	i = 0;
	info->envp = envp;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	info->paths = ft_split(ft_strchr(envp[i], '/'), ':');
}

static int 	process_line(char *line, t_shell_info *info)
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
		info.envp = envp;
		line = readline("minishell $> ");
		if (!line || !ft_strncmp(line, "exit", ft_strlen(line)))
			break ;
		process_line(line, &info);
		free(line);
	}
	eof();
	return (0);
}
