/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:36:13 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/07/10 10:35:50 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <fcntl.h>

extern int	g_errno;

void	restore_fd(t_exec *exec)
{
	dup2(exec->tmpin, 0);
	dup2(exec->tmpout, 1);
	close(exec->tmpin);
	close(exec->tmpout);
	waitpid(exec->pid, &exec->tmpret, 0);
}

void	waitchild(int pid, int exec_status)
{
	while (waitpid(pid, &exec_status, 0) > 0)
		;
	if (WIFSIGNALED(exec_status) && pid != -1)
		g_errno = 128 + WTERMSIG(exec_status);
	else if (pid != -1)
		g_errno = WEXITSTATUS(exec_status);
}

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

int	get_out_file(int tmpout, t_shell_info *info)
{
	int	fdout;

	if (info->outfile)
	{
		if (info->append > 0)
			fdout = open(info->outfile, O_APPEND | O_CREAT | O_RDWR,
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
		else
			fdout = open(info->outfile, O_RDWR | O_CREAT,
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	}
	else
		fdout = dup(tmpout);
	return (fdout);
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
