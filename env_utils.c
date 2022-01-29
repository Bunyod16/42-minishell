/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:38:53 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/29 20:04:44 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft/libft.h"

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
