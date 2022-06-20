/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:32:07 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/06/21 00:41:11 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	echo(int i, t_shell_info *info)
{
	int			j;
	int			should_nl;
	const char	*tmp = info->simple_commands[i].argv[1];

	j = 1;
	should_nl = 1;
	if (ft_strlen(tmp) == ft_strlen("-n") \
		&& !ft_strncmp(tmp, "-n", ft_strlen("-n")) && ++j)
		should_nl = 0;
	while (info->simple_commands[i].argv[j])
	{
		ft_putstr_fd(info->simple_commands[i].argv[j++], 1);
		if (info->simple_commands[i].argv[j])
			ft_putchar_fd(' ', 1);
	}
	if (should_nl)
		ft_putchar_fd('\n', 1);
}

void	pwd(void)
{
	char	*buf;
	char	*pwd;
	size_t	size;

	buf = 0;
	size = 0;
	pwd = getcwd(buf, size);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}

void	export(int i, t_shell_info *info)
{
	char	*tmp;
	char	*tmp_2;
	char	*tmp_3;

	if (info->simple_commands[i].argv[1] == 0)
	{
		i = -1;
		while (info->envp[++i])
		{
			tmp = info->envp[i];
			tmp_2 = ft_strchr(tmp, '=');
			tmp_3 = ft_substr(tmp, 0, ft_strlen(tmp) - ft_strlen(tmp_2));
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp_3, 1);
			free(tmp_3);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(tmp_2, 1);
			ft_putstr_fd("\"\n", 1);
		}
	}
	else
	{
		tmp = info->simple_commands[i].argv[1];
		set_env(info, tmp);
	}
}

void	unset(int i, t_shell_info *info)
{
	(void)i;
	(void)info;
}
