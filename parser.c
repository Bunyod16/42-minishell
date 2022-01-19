/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:55:22 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/19 18:16:09 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static int	lst_find(char *str, t_list *token_lst)
{
	while (token_lst)
	{
		if (ft_strncmp(token_lst->content, str, ft_strlen(str)) == 0
			&& ft_strlen(token_lst->content) == ft_strlen(str))
			return (1);
		token_lst = token_lst->next;
	}
	return (0);
}

static int	lst_count_str(char *str, t_list *token_lst)
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

int			count_cmd(t_list *token_lst)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = token_lst;
	while (temp)
	{
		if (ft_strncmp(temp->content, "|", ft_strlen(temp->content)) == 0
			|| ft_strncmp(temp->content, ">", ft_strlen(temp->content)) == 0
			|| ft_strncmp(temp->content, ">>", ft_strlen(temp->content)) == 0)
			return (count);
		count++;
		temp = temp->next;
	}
	return (count);
}

void		view_cmds(t_shell_info *info)
{
	int	i;
	int j;

	i = 0;
	while (info->simple_commands[i])
	{
		j = 0;
		while (info->simple_commands[i]->argv[j])
		{
			printf("%s\n",info->simple_commands[i]->argv[j]);
			j++;
		}
		i++;
	}
}

void		find_pipes(t_list *token_lst, t_shell_info *info)
{
	t_list			*temp;
	int				i;
	int				j;

	temp = token_lst;
	if (ft_strncmp(temp->content, "<", 1) == 0)
		temp = temp->next->next;
	info->simple_commands = malloc(sizeof(t_simple_command) * (lst_count_str("|", token_lst) + 2));
	j = 0;
	i = 0;
	info->simple_commands[i]->argv = malloc(sizeof(char **)*(count_cmd(temp) + 1));
	while (temp)
	{
		if (ft_strncmp(temp->content, "|", ft_strlen(temp->content)) == 0
			|| ft_strncmp(temp->content, ">", 1) == 0)
		{
			info->simple_commands[i]->argv[j] =	0;
			i++;
			info->simple_commands[i]->argv = malloc(sizeof(char **)*(count_cmd(temp->next) + 1));
			j = 0;
		}
		else
		{
			info->simple_commands[i]->argv[j] =	ft_strdup(temp->content);
			info->simple_commands[i]->argc = ++j;
		}
		temp = temp->next;
	}
	info->simple_commands[i]->argv[j] =	0;
	info->simple_commands[i + 1] = 0;
}

void		find_out_file(t_list *token_lst, t_shell_info *info)
{
	t_list *temp;

	temp = token_lst;
	while (temp)
	{
		if (!ft_strncmp(temp->content, ">", ft_strlen(temp->content)))
		{
			if (lst_find(">", temp->next) > 0)
				open(temp->next->content, O_CREAT);
			else
			{
				open(temp->next->content, O_WRONLY| O_CREAT);
				info->outfile = temp->next->content;
			}
		}
		if (!ft_strncmp(temp->content, ">>", ft_strlen(temp->content)))
		{
			if (lst_find(">", temp->next) > 0)
				open(temp->next->content, O_CREAT);
			else
			{
				open(temp->next->content, O_RDWR | O_CREAT | O_APPEND);
				info->outfile = temp->next->content;
			}
		}
		temp = temp->next;
	}
}

void		find_in_file(t_list *token_lst, t_shell_info *info)
{
	t_list *temp;

	temp = token_lst;
	while (temp)
	{
		if (!ft_strncmp(temp->content, "<", ft_strlen(temp->content)))
		{
			if (lst_find("<", temp->next) == 0)
				info->infile = temp->next->content;
		}
		temp = temp->next;
	}
}

t_cmd_list	*parser(t_list *token_lst, t_shell_info *info)
{
	int			len;
	t_list		*tmp;
	t_cmd_list	*ret;

	len = 0;
	ret = 0;
	tmp = token_lst;
	find_out_file(token_lst, info);
	find_in_file(token_lst, info);
	find_pipes(token_lst, info);
	view_cmds(info);
	while (tmp && ++len)
	{
		// printf("%s\n",(char *)tmp->content);
		tmp = tmp->next;
	}
	return (ret);
}
