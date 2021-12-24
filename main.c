/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:29:32 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/12/24 15:39:51 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "readline/history.h"
#include "readline/readline.h"

static void	action(int sig)
{
	if (sig == SIGINT)
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	if (argc != 1)
		return (1);
	signal(SIGINT, action);
	signal(SIGQUIT, action);
	printf("%s\n", readline("minishell $> "));
	return (0);
}
