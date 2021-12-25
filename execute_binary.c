/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:36:13 by bunyodshams       #+#    #+#             */
/*   Updated: 2021/12/25 13:03:54 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "minishell.h"

int	run_binary(char *binary, char **args, t_shell_info *info)
{
	int		i;
	char	*path_binary;

	i = -1;
	path_binary = ft_strjoin("/", binary);
	while (info->paths[++i])
		execve(ft_strjoin(info->paths[i], path_binary), args, info->envp);
	exit(0);
	return (0);
}
