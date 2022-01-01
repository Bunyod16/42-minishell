/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:59:53 by bshamsid          #+#    #+#             */
/*   Updated: 2022/01/01 16:32:14 by hbaddrul         ###   ########.fr       */
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

/* quotes.c */
void	balance_quotes(char **line);

/* lexer.c */
char	**lexer(char *line);

#endif
