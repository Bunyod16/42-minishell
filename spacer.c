/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:44:21 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/02 19:38:51 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"

#include <stdio.h>

static int	is_metachar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static void	set_quote(char *quote, char c)
{
	if (!*quote && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

void	spacer_before(char **line)
{
	int		i;
	char	quote;
	char	*tmp[2];

	quote = 0;
	i = -1;
	while ((*line)[++i])
	{
		set_quote(&quote, (*line)[i]);
		if (!quote && i > 0 && is_metachar((*line)[i]) \
				&& (*line)[i - 1] != (*line)[i] && (*line)[i - 1] != ' ')
		{
			tmp[0] = malloc(sizeof(char) * (ft_strlen(*line) + 1 + 1));
			if (!tmp[0])
				return ;
			ft_strlcpy(tmp[0], *line, ft_strlen(*line) + 1);
			tmp[0][i] = ' ';
			ft_strlcpy(tmp[0] + i + 1, *line + i, ft_strlen(*line) + 1 + 1);
			tmp[1] = *line;
			*line = tmp[0];
			free(tmp[1]);
			i = -1;
		}
	}
}

void	spacer_after(char **line)
{
	int		i;
	char	quote;
	char	*tmp[2];

	quote = 0;
	i = -1;
	while ((*line)[++i])
	{
		set_quote(&quote, (*line)[i]);
		if (!quote && is_metachar((*line)[i]) && (*line)[i + 1] != (*line)[i] \
				&& (*line)[i + 1] != ' ')
		{
			tmp[0] = malloc(sizeof(char) * (ft_strlen(*line) + 1 + 1));
			if (!tmp[0])
				return ;
			ft_strlcpy(tmp[0], *line, ft_strlen(*line) + 1);
			tmp[0][i + 1] = ' ';
			ft_strlcpy(tmp[0] + i + 1 + 1, *line + i + 1, \
					ft_strlen(*line) + 1 + 1);
			tmp[1] = *line;
			*line = tmp[0];
			free(tmp[1]);
			i = -1;
		}
	}
}

void	spacer(char **line)
{
	spacer_before(line);
	spacer_after(line);
}
