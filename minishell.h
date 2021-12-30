/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:59:53 by bshamsid          #+#    #+#             */
/*   Updated: 2021/12/30 18:21:33 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY 1

typedef struct s_shell_info
{
	int		envp_len;
	char	*pwd;
	char	*user;
	char	*prompt;
	char	**envp;
	char	**paths;
}	t_shell_info;

typedef struct s_token
{
	int		input_fd;
	int		input_redir;
	int		input_eof;
	int		output_fd;
	int		output_pipe;
	int		output_append;
	int		output_redir;
	char	*cmd;
	char	*str;
}	t_token;

/* execute_binary.c */
int     run_binary(char *binary, char **args, t_shell_info *info);

/* pipes.c */
t_token		*generate_tokens(char *line);
char		*clean_line(char *line);

#endif
