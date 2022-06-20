/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:49:30 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/06/21 00:57:18 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft/libft.h"

extern int	g_errno;

static char	*get_key(char *str)
{
	int		i;
	char	*ret;

	i = -1;
	while (str[++i])
		if (str[i] == ' ' || str[i] == '"' || str[i] == '\'')
			break ;
	ret = ft_substr(str, 0, i);
	return (ret);
}

void	expander(t_env_list **env, char **line, int *i)
{
	int		len;
	char	*key;
	char	*value;

	key = get_key(&(*line)[*i + 1]);
	value = get_env(env, key);
	len = ft_strlen(key);
	rm_substr(line, *i, len + 1);
	free(key);
	add_substr(line, *i, value);
	*i += ft_strlen(value) - 1;
}

void	errno_helper(char **line, int *i)
{
	char	*errno;

	rm_substr(line, *i, 2);
	errno = ft_itoa(g_errno);
	add_substr(line, *i, errno);
	*i += ft_strlen(errno) - 1;
}
