/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:36:13 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/07/07 03:07:50 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>

static char	**create_paths(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	**full_paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
		i++;
	full_paths = malloc(sizeof(char *) * (i + 2));
	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i])
	{
		full_paths[i] = ft_strjoin(paths[i], cmd);
		free(paths[i]);
	}
	free(paths);
	full_paths[i] = cmd;
	full_paths[i + 1] = 0;
	return (full_paths);
}

int	run_binary(int num, t_shell_info *info, t_exec exec)
{
	int			i;

	info->paths = create_paths(info->simple_commands[num].argv[0], info->envp);
	i = -1;
	close(exec.fdin);
	close(exec.fdout);
	while (info->paths[++i])
	{
		execve(info->paths[i], info->simple_commands[num].argv, info->envp);
		free(info->paths[i]);

	}
	free(info->paths);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(info->simple_commands[num].argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_all (info);
	exit (127);
}
