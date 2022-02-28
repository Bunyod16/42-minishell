/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:07:44 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/03/01 00:09:09 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
