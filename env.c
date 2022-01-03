/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:50:40 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/03 17:56:19 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft/libft.h"

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

char	**set_envp(t_env_list **env)
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

char	*get_env(t_env_list **env, char *key)
{
	t_env_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strlen(key) == ft_strlen(tmp->key) \
				&& !ft_strncmp(key, tmp->key, ft_strlen(key)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

void	set_env(t_shell_info *info, char *str)
{
	int		i;
	char	**tmp;

	env_add_back(&info->env, env_new(str));
	tmp = info->envp;
	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	info->envp = set_envp(&info->env);
}

void	unset_env(t_shell_info *info, char *key)
{
	int			i;
	char		**tmp_envp;
	t_env_list	*prev;
	t_env_list	*tmp_env;

	tmp_env = info->env;
	while (tmp_env)
	{
		if (ft_strlen(key) == ft_strlen(tmp_env->key) \
				&& !ft_strncmp(key, tmp_env->key, ft_strlen(key)))
		{
			env_del(tmp_env, free);
			prev->next = tmp_env->next;
		}
		prev = tmp_env;
		tmp_env = tmp_env->next;
	}
	tmp_envp = info->envp;
	i = 0;
	while (tmp_envp[i])
		free(tmp_envp[i++]);
	free(tmp_envp);
	info->envp = set_envp(&info->env);
}
