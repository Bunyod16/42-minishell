/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:07:44 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/06/19 16:42:39 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	lst_cnt(char *str, t_list *token_lst)
{
	int	count;

	count = 0;
	while (token_lst)
	{
		if (ft_strncmp(token_lst->content, str, ft_strlen(str)) == 0
			&& ft_strlen(token_lst->content) == ft_strlen(str))
			count++;
		token_lst = token_lst->next;
	}
	return (count);
}

int	count_cmd(t_list *token_lst)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = token_lst;
	while (temp && temp->content)
	{
		if (ft_strlen(temp->content) == 2
			&& ft_strncmp(temp->content, "<<", ft_strlen(temp->content)) == 0)
			count -= 2;
		if (ft_strlen(temp->content) == 1
			&& (ft_strncmp(temp->content, "|", ft_strlen(temp->content)) == 0 \
			|| ft_strncmp(temp->content, ">", ft_strlen(temp->content)) == 0))
			return (count);
		if (ft_strlen(temp->content) == 2
			&& ft_strncmp(temp->content, ">>", 2) == 0)
			return (count);
		count++;
		temp = temp->next;
	}
	return (count);
}

int	token_count(t_list *token_lst)
{
	int	i;

	i = 0;
	while (token_lst)
	{
		token_lst = token_lst->next;
		i++;
	}
	return (i);
}

t_simple_command	*pipe_cut(t_list *t, t_simple_command *p, t_shell_info *in)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (t && ft_strncmp(t->content, ">", 1) != 0)
	{
		if (ft_strlen(t->content) != 0
			&& ft_strncmp(t->content, "|", ft_strlen(t->content)) == 0)
		{
			i++;
			p[i].argv = malloc(sizeof(char *) * (count_cmd(t->next) + 1));
			j = 0;
			t = t->next;
		}
		if (ft_strlen(t->content) != 0)
		{
			p[i].argv[j] = ft_strdup(t->content);
			p[i].argc = ++j;
			p[i].argv[j] = 0;
		}
		t = t->next;
	}
	in->cmd_num = i;
	return (p);
}
