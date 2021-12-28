/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:59:53 by bshamsid          #+#    #+#             */
/*   Updated: 2021/12/28 17:13:18 by bunyodshams      ###   ########.fr       */
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
	int		output_fd;
	int		input_fd;
	int		wr_to_pipe;
	int		redir_input;
	int		redir_output;
	int		append_output;
	char	*str;
}	t_token;

/* execute_binary.c */
int     run_binary(char *binary, char **args, t_shell_info *info);

/* pipes.c */
t_token    *generate_tokens(char *line);

#endif
