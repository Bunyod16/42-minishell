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

void	free_mem(t_shell_info *info)
{
	int		i;
	int		j;

	if (info->outfile)
		free(info->outfile);
	if (info->infile)
		free(info->infile);
	if (info->here_doc)
		free(info->here_doc);
	i = 0;
	while (info->simple_commands && info->simple_commands[i].argv)
	{
		j = 0;
		while (info->simple_commands[i].argv \
			&& info->simple_commands[i].argv[j])
			free(info->simple_commands[i].argv[j++]);
		i++;
	}
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

void	bin_exit(t_shell_info *info, int i)
{
	int	len;
	int	exit_code;

	exit_code = 0;
	len = find_len(info->simple_commands[i].argv);

	// if not 1 arg too many args, give message and errno 1
	if (len > 2)
	{
		ft_putstr_fd("Too many arguements\n", 1);
		g_errno = 1;
		return ;
	}
	if (ft_isnum(info->simple_commands[i].argv[1]) == 0)
	{
		ft_putstr_fd("Arguement must be numeric\n", 1);
		exit_code = 255;
	}
	if (len == 2 && ft_isnum(info->simple_commands[i].argv[1]) == 1)
		exit_code = ft_atoi(info->simple_commands[i].argv[1]);

	rl_clear_history();
	env_clear(&info->env, free);
	i = 0;
	while (info->envp[i])
		free(info->envp[i++]);
	free(info->envp);
	free_mem(info);
	ft_putendl_fd("exit", 1);
	exit (exit_code);
}
