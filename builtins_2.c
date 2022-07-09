/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:01:47 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/07/09 16:46:52 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

extern int	g_errno;

void	env(t_shell_info *info)
{
	int	i;

	i = 0;
	while (info->envp[i])
		ft_putendl_fd(info->envp[i++], 1);
}

int	exp_uns_shld_return(int i, char *str, int should_free)
{
	if (!is_legal_identifier(i, str))
	{
		ft_putstr_fd("minishell: ", 2);
		if (i == 0)
			ft_putstr_fd("export", 2);
		else
			ft_putstr_fd("unset", 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		g_errno = 1;
		if (should_free)
			free(str);
		return (1);
	}
	return (0);
}
