/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:36:13 by bunyodshams       #+#    #+#             */
/*   Updated: 2021/12/25 03:21:54 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "unistd.h"
#include "stdlib.h"

int run_binary(char *binary, char **args, t_shell_info *info)
{
    int i;
	char *path_binary;

    i = -1;
    path_binary = ft_strjoin("/", binary);
    while (info->paths[++i])
        execve(ft_strjoin(info->paths[i], path_binary), args, info->envp);
	exit(0);
    return (0);
}