/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:12:57 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/06/24 01:18:58 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

extern int	g_errno;

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

void	restore_fd(t_exec *exec)
{
	dup2(exec->tmpin, 0);
	dup2(exec->tmpout, 1);
	close(exec->tmpin);
	close(exec->tmpout);
	waitpid(exec->pid, &exec->tmpret, 0);
}

void	save_fd_set_input(t_shell_info *info, t_exec *exec)
{
	int	fdin;

	exec->tmpin = dup(0);
	exec->tmpout = dup(1);
	if (info->infile)
		fdin = open(info->infile, O_RDONLY);
	else if (info->here_doc != 0)
		fdin = write_to_heredoc(info);
	else
		fdin = dup(exec->tmpin);
	exec->fdin = fdin;
	exec->pid = 111;
	exec->status = 0;
}

static void	run_cmd(int i, t_shell_info *info)
{
	const char	*cmd = info->simple_commands[i].argv[0];

	if (ft_strlen(cmd) == ft_strlen("echo") \
		&& !ft_strncmp(cmd, "echo", ft_strlen("echo")))
		echo(i, info);
	else if (ft_strlen(cmd) == ft_strlen("pwd") \
		&& !ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		pwd();
	else if (ft_strlen(cmd) == ft_strlen("env") \
		&& !ft_strncmp(cmd, "env", ft_strlen("env")))
		env(i, info);
	else if (ft_strlen(cmd) == ft_strlen("cd") \
		&& !ft_strncmp(cmd, "cd", ft_strlen("cd")))
		cd(i, info, 1);
	else
		run_binary(i, info);
	exit(0);
}

int	is_no_fork_builtin(int i, t_shell_info *info)
{
	char	*cmd;
	int			forked;

	i = 0;
	forked = 0;
	if (info->cmd_num == 0)
		forked = 1;
	cmd = info->simple_commands[i].argv[0];
	if (ft_strlen(cmd) == ft_strlen("cd") \
		&& !ft_strncmp(cmd, "cd", ft_strlen("cd")))
	{
		cd(i, info, 0);
		return (0);
	}
	else if (ft_strlen(cmd) == ft_strlen("export") \
		&& !ft_strncmp(cmd, "export", ft_strlen("export")))
	{
		export(i, info);
		return (1);
	}
	else if (ft_strlen(cmd) == ft_strlen("unset") \
		&& !ft_strncmp(cmd, "unset", ft_strlen("unset")))
	{
		unset(i, info);
		return (1);
	}
	return (0);
}

void	executor(t_shell_info *info)
{
	int			i;
	t_exec		exec;

	save_fd_set_input(info, &exec);
	i = -1;
	while (info->cmd_num >= ++i)
	{
		dup2(exec.fdin, 0);
		close(exec.fdin);
		if (i == info->cmd_num)
			exec.fdout = get_out_file(exec.tmpout, info);
		else
		{
			pipe(exec.fdpipe);
			exec.fdout = exec.fdpipe[1];
			exec.fdin = exec.fdpipe[0];
		}
		dup2(exec.fdout, 1);
		close(exec.fdout);
		exec.pid = fork();
		if (exec.pid == 0)
			run_cmd(i, info);
		waitpid(exec.pid, &exec.status, 0);
		g_errno = WEXITSTATUS(exec.status);
		is_no_fork_builtin(i, info);
	}
	restore_fd(&exec);
}
