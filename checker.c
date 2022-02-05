/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 23:56:45 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/29 19:56:17 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft/libft.h"

static int	is_metachar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static int	is_valid_operator(char *next_token)
{
	char	*tmp;

	if (!next_token || is_metachar(next_token[0]))
	{
		tmp = ft_strdup("minishell: syntax error near unexpected token `'");
		if (!next_token)
			add_substr(&tmp, ft_strlen(tmp) - 1, "newline");
		else if (is_metachar(next_token[0]))
			add_substr(&tmp, ft_strlen(tmp) - 1, next_token);
		ft_putendl_fd(tmp, 2);
		free(tmp);
		return (0);
	}
	return (1);
}

static int	is_valid_in_redir(char *token, char *next_token)
{
	char	*tmp;

	if (token[0] == '<' && ft_strlen(token) == 1 \
			&& open(next_token, O_RDONLY) == -1)
	{
		tmp = ft_strdup("minishell: ");
		add_substr(&tmp, ft_strlen(tmp), next_token);
		perror(tmp);
		free(tmp);
		return (0);
	}
	return (1);
}

int	is_syntax_cmd(t_list *token_lst)
{
	char	*token;
	char	*next_token;
	t_list	*tmp;

	tmp = token_lst;
	while (tmp)
	{
		token = tmp->content;
		if (is_metachar(token[0]))
		{
			next_token = 0;
			if (tmp->next)
				next_token = tmp->next->content;
			if (!is_valid_operator(next_token) \
					|| !is_valid_in_redir(token, next_token))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
