/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:55:22 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/07/06 18:25:18 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static void	skip_here_doc(t_list **token_lst, t_shell_info *info)
{
	t_list	*ret;

	ret = *token_lst;
	if (token_count(*token_lst) < 3)
		return ;
	if (ft_strncmp("<<", (*token_lst)->content,
			ft_strlen((*token_lst)->content)) == 0
		&& (ft_strlen((*token_lst)->content) == ft_strlen("<<")))
	{
		ret = (*token_lst)->next->next;
		info->here_doc = ft_strdup((*token_lst)->next->content);
		free((*token_lst)->next);
		free(*token_lst);
		*token_lst = ret;
	}
	else if (ft_strncmp("<<", (*token_lst)->next->content,
			ft_strlen((*token_lst)->next->content)) == 0
		&& (ft_strlen((*token_lst)->next->content) == ft_strlen("<<")))
	{
		info->here_doc = ft_strdup((*token_lst)->next->next->content);
		ret = (*token_lst)->next->next->next;
		ft_lstdelone((*token_lst)->next->next, free);
		ft_lstdelone((*token_lst)->next, free);
		(*token_lst)->next = ret;
	}
}

t_simple_command	*find_pipes(t_list **token_lst, t_shell_info *info)
{
	t_simple_command	*pipes;
	t_list				*temp;

	temp = skip_infiles(*token_lst);
	pipes = malloc(sizeof(t_simple_command) * (lst_cnt("|", temp) + 2));
	pipes[0].argv = malloc(sizeof(char *) * (count_cmd(temp) + 1));
	pipes = pipe_cut(temp, pipes, info);
	return (pipes);
}

void	find_out_file(t_list *token_lst, t_shell_info *info)
{
	t_list	*temp;

	temp = token_lst;
	info->append = 0;
	while (temp)
	{
		if (ft_strlen(temp->content) != 0 \
			&& (ft_strncmp(temp->content, ">", ft_strlen(temp->content)) == 0
			|| ft_strncmp(temp->content, ">>", ft_strlen(temp->content)) == 0))
		{
			if (ft_strncmp(temp->content, ">>", ft_strlen(temp->content)) == 0
			&& ft_strlen(temp->content) == 2)
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
		if (ft_strncmp(temp->content, "<<", ft_strlen(temp->content)) == 0
			&& ft_strlen(temp->content) == ft_strlen("<<"))
			return ;
		if (ft_strncmp(temp->content, "<", ft_strlen(temp->content)) == 0
			&& ft_strlen(temp->content) == ft_strlen("<"))
			info->infile = ft_strdup(temp->next->content);
		temp = temp->next;
	}
}

void	parser(t_list **token_lst, t_shell_info *info)
{
	find_out_file(*token_lst, info);
	find_in_file(*token_lst, info);
	skip_here_doc(token_lst, info);
	info->simple_commands = find_pipes(token_lst, info);
}
