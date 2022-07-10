/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exit.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/06/24 01:25:09 by bunyodshams	   #+#	#+#			 */
/*   Updated: 2022/07/06 00:31:23 by hbaddrul		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

extern int	g_errno;

void	free_inoutfile(t_shell_info *info)
{
	if (info->outfile)
		free(info->outfile);
	if (info->infile)
		free(info->infile);
	if (info->here_doc)
		free(info->here_doc);
}

void	free_all(t_shell_info *info)
{
	int	i;

	env_clear(&info->env, free);
	free_simple_commands(info);
	i = 0;
	while (info->envp[i])
		free(info->envp[i++]);
	free(info->envp);
	free_inoutfile(info);
}

void	free_simple_commands(t_shell_info *info)
{
	int	num;
	int	i;

	num = 0;
	while (num <= info->cmd_num)
	{
		i = 0;
		while (info->simple_commands[num].argv[i] \
			&& i < info->simple_commands[num].argc)
			free(info->simple_commands[num].argv[i++]);
		free(info->simple_commands[num++].argv);
	}
	free(info->simple_commands);
}

int	ft_isnum(char *str)
{
	while (str && *str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

void	bin_exit(t_shell_info *info, int i, int pid, int len)
{
	int	exit_code;

	exit_code = 0;
	if (len > 1 && ft_isnum(info->simple_commands[i].argv[1]) == 0)
	{
		if (pid != 0)
			ft_putstr_fd("numeric arguement required\n", 2);
		exit_code = 255;
	}
	else if (len > 2)
	{
		g_errno = 1;
		if (pid == 1)
			return ;
		ft_putstr_fd("Too many arguements\n", 2);
		exit_code = 1;
	}
	else if (len == 2 && ft_isnum(info->simple_commands[i].argv[1]) == 1)
		exit_code = ft_atoi(info->simple_commands[i].argv[1]);
	rl_clear_history();
	free_all(info);
	if (pid != 0)
		ft_putendl_fd("exit", 1);
	exit (exit_code);
}
