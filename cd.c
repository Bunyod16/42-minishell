#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include <stdio.h>

int		find_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	change_dir(t_shell_info *info, char *path)
{
	char	*cwd;
	char	*temp;

	if (path == NULL)
		return ;
	cwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
		printf("cd: No such file or directory: %s\n", path);
	else
	{
		unset_env(info, "OLDPWD");;
		temp = ft_strjoin("OLDPWD=", cwd);
		set_env(info,temp);
		free(temp);
	}
}

void	cd(int i, t_shell_info *info)
{
	int		len;
	char *path;

	len = find_len(info->simple_commands[i].argv);
	if (len > 2)
	{
		printf("cd: Error, more than 2 arguements");
		return ;
	}
	else if (len == 1)
	{
		change_dir(info, get_env(&info->env, "HOME"));
		return ;
	}
	else
	{
		path = info->simple_commands[i].argv[1];
		if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
			change_dir(info, get_env(&info->env, "OLDPWD"));
		else
			change_dir(info, path);
	}
}