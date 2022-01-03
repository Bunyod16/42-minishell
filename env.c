/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:50:40 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/03 15:25:18 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

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

t_env_list	*init_env(char **envp)
{
	int			i;
	t_env_list	*env;

	env = 0;
	i = -1;
	while (envp[++i])
		env_add_back(&env, env_new(envp[i]));
	return (env);
}

char	**env_to_char(t_env_list **env)
{
	int			i;
	int			len;
	char		**ret;
	t_env_list	*tmp;

	tmp = *env;
	len = 1;
	while (tmp->next && ++len)
		tmp = tmp->next;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (0);
	i = 0;
	tmp = *env;
	while (tmp)
	{
		ret[i++] = ft_strdup(tmp->full);
		tmp = tmp->next;
	}
	ret[i] = 0;
	return (ret);
}
