/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:29:32 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/12/24 16:54:45 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "readline/history.h"
#include "readline/readline.h"
#include "minishell.h"

static void	action(int sig)
{
	if (sig == SIGINT)
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	char			*line;
	t_shell_info 	info;

	if (argc != 1)
		return (1);
	signal(SIGINT, action);
	signal(SIGQUIT, action);
	while (1)
	{
		line = readline("minishell $> ");
		info.envp = envp;
		echo_test(line, &info);
	}
	return (0);
}
