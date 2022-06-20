/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 01:10:49 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/06/21 01:15:29 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_mem(t_shell_info *info)
{
	int		i;
	int		j;

	if (info->outfile)
		free(info->outfile);
	if (info->infile)
		free(info->infile);
	if (info->here_doc)
		free(info->here_doc);
	i = 0;
	while (info->simple_commands && info->simple_commands[i].argv)
	{
		j = 0;
		while (info->simple_commands[i].argv \
			&& info->simple_commands[i].argv[j])
			free(info->simple_commands[i].argv[j++]);
		i++;
	}
}
