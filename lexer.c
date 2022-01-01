/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:09:39 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/01 16:33:08 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"

static void	set_quote(char *quote, char c)
{
	if (!*quote && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

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

char	**lexer(char *line)
{
	int		i;
	int		len;
	char	quote;
	char	**ret;

	ret = malloc(sizeof(char *) * (toklen(line) + 1));
	if (!ret)
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
				ret[i++] = ft_substr(line - len, 0, len);
		}
		else if (++line && quote)
			++len;
	}
	ret[i] = 0;
	return (ret);
}
