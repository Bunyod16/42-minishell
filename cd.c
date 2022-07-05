#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include <stdio.h>

extern int	g_errno;

int		find_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	change_dir(t_shell_info *info, char *path, int forked)
{
	char	*cwd;
	char	*temp;

	if (path == NULL)
		return ;
	cwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		if (forked)
			ft_putstr_fd("cd: No such file or directory\n", 1);
		g_errno = 1;
		return ;
	}
	unset_env(info, "OLDPWD");
	temp = ft_strjoin("OLDPWD=", cwd);
	set_env(info,temp);
	free(temp);
	cwd = getcwd(NULL, 0);
	unset_env(info, "PWD");
	temp = ft_strjoin("PWD=", cwd);
	set_env(info, temp);
	free(temp);
	g_errno = 1;
}

void	cd(int i, t_shell_info *info, int forked)
{
	int		len;
	char *path;

	len = find_len(info->simple_commands[i].argv);
	if (len > 2)
	{
		if (forked)
			ft_putstr_fd("cd: Error, more than 2 arguements\n", 1);
		return ;
	}
	else if (len == 1)
	{
		change_dir(info, get_env(&info->env, "HOME"), forked);
		return ;
	}
	else
	{
		path = info->simple_commands[i].argv[1];
		if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
			change_dir(info, get_env(&info->env, "OLDPWD"), forked);
		else
			change_dir(info, path, forked);
	}
}