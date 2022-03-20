/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 02:35:48 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/03/20 12:10:11 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	check_eof(char *eof, char *line)
{
	if (!eof || !*eof || !line || !*line)
		return (0);
	if (ft_strlen(line) == ft_strlen(eof)
		&& ft_strncmp(line, eof, ft_strlen(line)) == 0)
		return (1);
	return (0);
}

char	*copy_args(char *args, char *tmp, char *new_args)
{
	int	i;

	i = 0;
	while (args != NULL && args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	while (tmp != NULL && tmp[i - ft_strlen(args)])
	{
		new_args[i] = tmp[i - ft_strlen(args)];
		i++;
	}
	return (new_args);
}

char	*word_splitter(char *tmp, char *hdoc, char *new_args, char *args)
{
	while ((!tmp || !*tmp) || !check_eof(hdoc, tmp))
	{
		if (new_args != NULL)
		{
			args = ft_strdup(new_args);
			free(new_args);
		}
		new_args = malloc(sizeof(char) * (ft_strlen(tmp)
					+ ft_strlen(args) + 2));
		new_args = copy_args(args, tmp, new_args);
		new_args[ft_strlen(tmp) + ft_strlen(args)] = '\n';
		new_args[ft_strlen(tmp) + ft_strlen(args) + 1] = 0;
		free(args);
		free(tmp);
		tmp = readline(">");
	}
	return (new_args);
}

int	write_to_heredoc(t_shell_info *info)
{
	char		*args;
	char		*tmp;
	char		*new_args;
	int			h_pipe[2];

	args = 0;
	new_args = 0;
	tmp = readline(">");
	new_args = word_splitter(tmp, info->here_doc, new_args, args);
	pipe(h_pipe);
	write(h_pipe[1], new_args, ft_strlen(new_args));
	close(h_pipe[1]);
	return (h_pipe[0]);
}
