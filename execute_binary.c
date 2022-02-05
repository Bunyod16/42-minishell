/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:36:13 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/02/04 04:13:34 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>


static char	**create_paths(char *cmd,char **envp)
{
	int		i;
	char	**paths;
	char	**full_paths;

	i = 0;
	while(envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
		i++;
	full_paths = malloc(sizeof(char *) * (i + 1));
	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i])
		full_paths[i] = ft_strjoin(paths[i], cmd);
	full_paths[i] = 0;
	return (full_paths);
}

int	run_binary(int cmd_num, t_shell_info *info)
{
	int			i;
	char		**args;
	char		*cmd;
	pid_t		pid;

	printf("ran\n");
	cmd = info->simple_commands[cmd_num].argv[0];
	args = malloc(sizeof(char **) * (info->simple_commands[cmd_num].argc));
	i = 1;
	while (info->simple_commands[cmd_num].argv[i])
	{
		args[i - 1] = ft_strdup(info->simple_commands[cmd_num].argv[i]);
		i++;
	}
	args[i - 1] = 0;
	i = -1;
	info->paths = create_paths(info->simple_commands[cmd_num].argv[0], info->envp);
	pid = fork();
	while (info->paths[++i])
	{
		execve(info->paths[i], info->simple_commands[cmd_num].argv, info->envp);
	}
	return (0);
}