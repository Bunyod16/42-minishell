/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 00:02:21 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/30 17:37:35 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft/libft.h"
#include "libreadline/history.h"
#include "libreadline/readline.h"

static char	get_first_quote(char *line)
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

static char	*readline_quote(char **line)
{
	char	*ret;
	char	*tmp;
	char	*line_2;

	line_2 = readline("quote $> ");
	if (!line_2)
	{
		ft_putendl_fd(\
				"minishell: unexpected EOF while looking for matching `'", 2);
		free(*line);
		*line = 0;
		return (0);
	}
	tmp = ft_strjoin(*line, "\n");
	free(*line);
	ret = ft_strjoin(tmp, line_2);
	free(tmp);
	free(line_2);
	*line = ret;
	return (ret);
}

void	set_quote(char *quote, char c)
{
	if (!*quote && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

void	quoter(char **line)
{
	char	*str;
	char	quotes[2];

	quotes[0] = get_first_quote(*line);
	quotes[1] = quotes[0];
	if (quotes[1])
	{
		str = ft_strchr(*line, quotes[1]);
		while (str)
		{
			str = ft_strchr(++str, quotes[1]);
			if (!str)
			{
				str = readline_quote(line);
				quotes[1] = quotes[0];
			}
			else
				quotes[1] = get_first_quote(++str);
			if (!str || !quotes[1])
				break ;
			str = ft_strchr(str, quotes[1]);
		}
	}
}

void	dequoter(t_env_list **env, char **line)
{
	int		i;
	int		should_get_quote;
	char	quote;

	should_get_quote = 0;
	quote = 0;
	i = -1;
	while ((*line)[++i])
	{
		if (!should_get_quote)
			quote = get_first_quote(&((*line)[i]));
		if (quote != '\'' && (*line)[i] == '$')
			expander(env, line, &i);
		if (quote && (*line)[i] == quote)
		{
			rm_substr(line, i--, 1);
			should_get_quote ^= 1;
		}
	}
}
