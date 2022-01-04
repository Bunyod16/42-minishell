/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:55:22 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/05 00:29:41 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_list	*parser(t_list *token_lst)
{
	int			len;
	t_list		*tmp;
	t_cmd_list	*ret;

	len = 0;
	ret = 0;
	tmp = token_lst;
	while (tmp && ++len)
		tmp = tmp->next;
	return (ret);
}
