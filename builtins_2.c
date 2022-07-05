/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:01:47 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/07/06 00:33:44 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	env(t_shell_info *info)
{
	int	i;

	i = 0;
	while (info->envp[i])
	{
		printf("%s\n", info->envp[i++]);
	}
}
