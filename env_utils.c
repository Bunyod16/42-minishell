/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:38:53 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/07/09 16:06:47 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft/libft.h"

void	env_del(t_env_list *env, void (*del)(void *))
{
	del(env->key);
	del(env->value);
	del(env->full);
	free(env);
}

void	env_clear(t_env_list **env, void (*del)(void *))
{
	if (env && *env)
	{
		env_clear(&(*env)->next, del);
		env_del(*env, del);
		*env = 0;
	}
}

void	env_add_back(t_env_list **env, t_env_list *new)
{
	t_env_list	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env_list	*env_new(char *str)
{
	char		*tmp;
	t_env_list	*ret;

	ret = malloc(sizeof(t_env_list));
	if (!ret)
		return (0);
	tmp = ft_strchr(str, '=');
	ret->key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(tmp));
	ret->value = ft_strdup(tmp + 1);
	ret->full = ft_strdup(str);
	ret->next = 0;
	return (ret);
}

int	is_legal_identifier(int cmd, char *key)
{
	int	i;

	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (0);
	i = 0;
	while (key[++i])
	{
		if (key[i] == '=')
		{
			if (cmd)
				return (0);
			return (1);
		}
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (0);
	}
	return (1);
}
