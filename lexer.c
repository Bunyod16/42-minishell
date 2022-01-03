/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:09:39 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/03 11:40:29 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft/libft.h"

static int	toklen(char *line)
{
	int		ret;
	char	quote;

	ret = 0;
	quote = 0;
	while (*line)
	{
		if (*line != ' ')
		{
			if (!quote)
				++ret;
			while (*line && *line != ' ')
				set_quote(&quote, *line++);
		}
		else
			++line;
	}
	return (ret);
}

static int	tokeniser(char ***tokens, char *line)
{
	int		i;
	int		len;
	char	quote;

	*tokens = malloc(sizeof(char *) * (toklen(line) + 1));
	if (!(*tokens))
		return (0);
	i = 0;
	while (*line)
	{
		if (*line != ' ')
		{
			if (!quote)
				len = 0;
			while (*line && *line != ' ' && ++len)
				set_quote(&quote, *line++);
			if (!quote)
				(*tokens)[i++] = ft_substr(line - len, 0, len);
		}
		else if (++line && quote)
			++len;
	}
	(*tokens)[i] = 0;
	return (i);
}

t_list	*lexer(char *line)
{
	int		len;
	char	**tokens;
	t_list	*ret;

	len = tokeniser(&tokens, line);
	ret = 0;
	while (len--)
		ft_lstadd_front(&ret, ft_lstnew(tokens[len]));
	free(tokens);
	return (ret);
}
