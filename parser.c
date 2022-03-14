/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:55:22 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/03/12 17:23:26 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static t_list	*skip_here_doc(t_list *token_lst)
{
	t_list	*temp;

	temp = token_lst;
	if (ft_strncmp("<<", temp->content, ft_strlen(temp->content)) == 0
		&& (ft_strlen(temp->content) == ft_strlen("<<")))
		temp = temp->next->next;
	return (temp);
}

t_simple_command	*find_pipes(t_list *token_lst, t_shell_info *info)
{
	t_simple_command	*pipes;
	t_list				*temp;
	int					i;
	int					j;

	temp = skip_here_doc(token_lst);
	if (ft_strncmp(temp->content, "<", 1) == 0)
		temp = temp->next->next; 
	pipes = malloc(sizeof(t_simple_command) * (lst_cnt("|", token_lst) + 2));
	j = 0;
	i = 0;
	pipes[0].argv = malloc(sizeof(char *) * (count_cmd(temp) + 1));
	while (temp && ft_strncmp(temp->content, ">", 1) != 0)
	{
		if (ft_strncmp(temp->content, "|", ft_strlen(temp->content)) == 0)
		{
			i++;
			pipes[i].argv = malloc(sizeof(char *)
					* (count_cmd(temp->next) + 1));
			j = 0;
			temp = temp->next;
		}
		pipes[i].argv[j] = ft_strdup(temp->content);
		pipes[i].argc = ++j;
		pipes[i].argv[j] = 0;
		temp = temp->next;
	}
	info->cmd_num = i;
	return (pipes);
}

void	find_out_file(t_list *token_lst, t_shell_info *info)
{
	t_list	*temp;

	temp = token_lst;
	info->append = 0;
	while (temp)
	{
		if (ft_strncmp(temp->content, ">", ft_strlen(temp->content)) == 0)
		{
			if (ft_strncmp(temp->content, ">>", ft_strlen(temp->content)) == 0)
				info->append = 1;
			info->outfile = ft_strdup(temp->next->content);
		}
		temp = temp->next;
	}
}

void	find_in_file(t_list *token_lst, t_shell_info *info)
{
	t_list	*temp;

	temp = token_lst;
	while (temp)
	{
		if (ft_strncmp(temp->content, "<", ft_strlen(temp->content)) == 0
			&& ft_strlen(temp->content) == ft_strlen("<"))
			info->infile = ft_strdup(temp->next->content);
		if (ft_strncmp(temp->content, "<<", ft_strlen(temp->content)) == 0
			&& ft_strlen(temp->content) == ft_strlen("<<"))
			info->here_doc = ft_strdup(temp->next->content);
		temp = temp->next;
	}
}

void	parser(t_list *token_lst, t_shell_info *info)
{
	find_out_file(token_lst, info);
	find_in_file(token_lst, info);
	info->simple_commands = find_pipes(token_lst, info);
}
