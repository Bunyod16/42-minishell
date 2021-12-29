/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 00:02:21 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/12/29 13:24:12 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft/libft.h"
#include "libreadline/history.h"
#include "libreadline/readline.h"

static char	get_quote(char *line)
{
	char	ret;
	char	*strs[2];

	ret = 0;
	strs[0] = ft_strchr(line, '"');
	strs[1] = ft_strchr(line, '\'');
	if (!strs[0] && strs[1])
		ret = '\'';
	else if (strs[0] && !strs[1])
		ret = '"';
	else if (strs[0] && strs[1])
	{
		if (ft_strlen(strs[0]) > ft_strlen(strs[1]))
			ret = '"';
		else
			ret = '\'';
	}
	return (ret);
}

static char	*read_quote_line(char **line)
{
	char	*ret;
	char	*tmp;
	char	*line_2;

	tmp = ft_strjoin(*line, "\n");
	free(*line);
	line_2 = readline("dquote $> ");
	ret = ft_strjoin(tmp, line_2);
	free(tmp);
	free(line_2);
	*line = ret;
	return (ret);
}

void	balance_quotes(char **line)
{
	char	*str;
	char	quotes[2];

	quotes[0] = get_quote(*line);
	quotes[1] = quotes[0];
	if (quotes[1])
	{
		str = ft_strchr(*line, quotes[1]);
		while (str)
		{
			str = ft_strchr(++str, quotes[1]);
			if (!str)
			{
				str = read_quote_line(line);
				quotes[1] = quotes[0];
			}
			else
			{
				quotes[1] = get_quote(++str);
				if (!quotes[1])
					break ;
			}
			str = ft_strchr(str, quotes[1]);
		}
	}
}
