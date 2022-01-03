/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:29:32 by hbaddrul          #+#    #+#             */
/*   Updated: 2022/01/03 18:05:05 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "libft/libft.h"
#include "libreadline/history.h"
#include "libreadline/readline.h"

static void	action(int sig)
{
	if (sig == SIGINT)
		ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	update_prompt(t_shell_info *info)
{
	char	*pwd;
	char	*user;
	char	*prompt;

	pwd = ft_strrchr(getenv("PWD"), '/') + 1;
	user = getenv("USER");
	prompt = malloc(sizeof(char) * (ft_strlen(user) + ft_strlen(pwd) + 15 + 1));
	if (!prompt)
		perror("malloc error");
	ft_strlcpy(prompt, user, ft_strlen(user) + 1);
	ft_strlcat(prompt, "@minishell ", ft_strlen(prompt) + 11 + 1);
	ft_strlcat(prompt, pwd, ft_strlen(prompt) + ft_strlen(pwd) + 1);
	ft_strlcat(prompt, " $> ", ft_strlen(prompt) + 4 + 1);
	info->prompt = ft_strdup(prompt);
	free(prompt);
}

static void	exec(char *line, t_shell_info *info)
{
	int		i;
	char	*bin;
	char	*tmp;
	char	**argv;
	char	**paths;

	argv = ft_split(line, ' ');
	paths = ft_split(getenv("PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		bin = ft_strjoin(tmp, argv[0]);
		free(tmp);
		execve(bin, argv, info->envp);
		free(bin);
		free(paths[i]);
	}
	free(paths);
	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

// possibly handle quotes etc before calling exec below
static void	process_line(char *line, t_shell_info *info)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork error");
	else if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid error");
		return ;
	}
	exec(line, info);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*token_list;
	t_shell_info	info;

	(void)argv;
	if (argc != 1)
		return (1);
	if (signal(SIGINT, action) == SIG_ERR || signal(SIGQUIT, action) == SIG_ERR)
		perror("signal error");
	info.env = init_env(envp);
	info.envp = set_envp(&info.env);
	set_env(&info, "LOL=hehe");
	printf("%s\n", get_env(&info.env, "LOL"));
	unset_env(&info, "LOL");
	printf("%s\n", get_env(&info.env, "LOL"));
	while (1)
	{
		update_prompt(&info);
		line = readline(info.prompt);
		free(info.prompt);
		if (!line || (ft_strlen(line) == 4 && !ft_strncmp(line, "exit", 4)))
			break ;
		if (!ft_strlen(line))
			continue ;
		quoter(&line);
		add_history(line);
		spacer(&line);
		token_list = lexer(line);
		ft_lstclear(&token_list, free);
		process_line(line, &info);
		free(line);
	}
	return (0);
}
