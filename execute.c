/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:12:57 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/02/08 22:12:59 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

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

int	save_fd_set_input(t_shell_info *info, t_exec *exec)
{
	int	fdin;

	exec->tmpin = dup(0);
	exec->tmpout = dup(1);
	if (info->infile)
		fdin = open(info->infile, O_RDONLY);
	else
		fdin = dup(exec->tmpin);
	return (fdin);
}

void	executor(t_shell_info *info)
{
	int			i;
	t_exec		exec;

	exec.fdin = save_fd_set_input(info, &exec);
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
			run_binary(i, info);
	}
	restore_fd(&exec);
}
