/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:39:38 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/02/01 23:09:33 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

// static void	executor(t_shell_info *info)
// {
// 	int tmpin;
// 	int tmpout;
// 	int	fdin;
// 	int	ret;
// 	int fdout;
// 	int	fdpipe[2];
// 	int	i;
// 	int tmp;
// 	int count;

// 	count = info->cmd_num;
// 	tmpin = dup(0);
// 	tmpout = dup(1);
// 	if (info->infile != 0)
// 		fdin = open(info->infile, O_RDONLY);
// 	else
// 		fdin = dup(tmpin);
// 	i = 0;

// 	while (count)
// 	{
// 		dup2(fdin, 0);
// 		close(fdin);
// 		if (info->cmd_num - 1 == 0)
// 		{
// 			if (info->outfile)
// 				fdout = open(info->outfile, O_WRONLY);
// 			else
// 				fdout = dup(tmpout);
// 		}
// 		else
// 		{
// 			pipe(fdpipe);
// 			fdout = fdpipe[1];
// 			fdin = fdpipe[0];
// 		}
// 		dup2(fdout, 1);
// 		close(fdout);
// 		ret = fork();
// 		if (ret == 0)
// 		{
// 			run_binary(i, info);
// 			i++;
// 		}
// 		count--;
// 	}
// 	dup2(tmpin, 0);
// 	dup2(tmpout, 1);
// 	close(tmpin);
// 	close(tmpout);

// 	waitpid(ret, &tmp, 0);
// }

void	executor(t_shell_info *info)
{
    int tmpin=dup(0);
    int tmpout=dup(1);
    int fdin;
	int tmpret;

    if (info->infile)
        fdin = open(info->infile, O_RDONLY);
    else
       fdin = dup(tmpin);

    int ret;
    int fdout;
    int i;
    
    i = 0;
    while (info->cmd_num > i++)
    {
        //redirect input
        dup2(fdin, 0);
        close(fdin);
        //setup output
        if (i == info->cmd_num)
        {
        // LAST simple command 
            if(info->outfile)
                fdout = open(info->outfile, O_WRONLY);
            else
                fdout=dup(tmpout);
        }
        else
		{
			// NOT LAST simple command
			//create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
        }// if/else
        // Redirect output
        dup2(fdout,1); 
        close(fdout);

        // Create child process
        ret=fork(); 
        if(ret==0)
        	run_binary(i, info);
    }
    //restore in/out defaults
    dup2(tmpin,0);
    dup2(tmpout,1);
	printf("out\n");
    close(tmpin);
    close(tmpout);
    waitpid(ret, &tmpret, 0);
    // execute
}