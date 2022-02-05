/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:43:38 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/30 01:19:34 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"

void	add_substr(char **str, int start, char *substr)
{
	char	*tmp[2];

	tmp[0] = malloc(sizeof(char) * (ft_strlen(*str) + ft_strlen(substr) + 1));
	if (!tmp[0])
		return ;
	ft_strlcpy(tmp[0], *str, start + 1);
	ft_strlcpy(tmp[0] + start, substr, start + ft_strlen(substr) + 1);
	ft_strlcpy(tmp[0] + start + ft_strlen(substr), *str + start, \
			ft_strlen(*str) + ft_strlen(substr) + 1);
	tmp[1] = *str;
	*str = tmp[0];
	free(tmp[1]);
}

void	rm_substr(char **str, int start, int len)
{
	char	*tmp[2];

	tmp[0] = malloc(sizeof(char) * (ft_strlen(*str) - len + 1));
	if (!tmp[0])
		return ;
	ft_strlcpy(tmp[0], *str, start + 1);
	ft_strlcpy(tmp[0] + start, *str + start + len, \
			ft_strlen(*str + start + len) + 1);
	tmp[1] = *str;
	*str = tmp[0];
	free(tmp[1]);
}
