/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:39:38 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/02/06 19:48:03 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void	executor(t_shell_info *info)
{
    int tmpin;
    int tmpout;
    int fdpipe[2];
    int tmpret;
    int fdin;
    int fdout;
    pid_t pid;
    int i;

    tmpin = dup(0);
    tmpout = dup(1);
    if (info->infile)
        fdin = open(info->infile, O_RDONLY);
    else
        fdin = dup(tmpin);

    i = -1;
    while (info->cmd_num >= ++i)
    {
        dup2(fdin, 0);
        close(fdin);
        if (i == info->cmd_num)
        {
            if (info->outfile)
                fdout = open(info->outfile, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
            else
                fdout = dup(tmpout);
        }
        else
        {
            pipe(fdpipe);
            fdout = fdpipe[1];
            fdin = fdpipe[0];
        }
        dup2(fdout, 1);
        close(fdout);

        pid = fork();
        if(pid == 0)
        	run_binary(i, info);
    }
    dup2(tmpin,0);
    dup2(tmpout,1);
    close(tmpin);
    close(tmpout);
    waitpid(pid, &tmpret, 0);
    // execute
}