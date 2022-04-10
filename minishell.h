/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:59:53 by bshamsid          #+#    #+#             */
/*   Updated: 2022/04/10 16:01:42 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY 1

# include "libft/libft.h"
# include <sys/types.h>

typedef struct s_env_list
{
	char				*key;
	char				*value;
	char				*full;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_cmd_list
{
	char				**cmds;
	struct s_cmd_list	*next;
}	t_cmd_list;

typedef struct s_simple_command
{
	int		argc;
	char	**argv;
}	t_simple_command;

typedef struct s_shell_info
{
	char				*prompt;
	char				**envp;
	char				**paths;
	char				*infile;
	char				*outfile;
	int					cmd_num;
	int					append;
	char				*here_doc;
	t_env_list			*env;
	t_simple_command	*simple_commands;
}	t_shell_info;

typedef struct s_exec
{
	int		tmpin;
	int		tmpout;
	int		fdpipe[2];
	int		tmpret;
	int		fdin;
	int		fdout;
	pid_t	pid;

}	t_exec;

/* env.c */
void				set_env(t_shell_info *info, char *str);
void				unset_env(t_shell_info *info, char *key);
char				*get_env(t_env_list **env, char *key);
char				**set_envp(t_env_list *env);
t_env_list			*init_env(char **envp);

/* env_utils.c */
void				env_del(t_env_list *env, void (*del)(void *));
void				env_clear(t_env_list **env, void (*del)(void *));
void				env_add_back(t_env_list **env, t_env_list *new);
t_env_list			*env_new(char *str);

/* quotes.c */
void				quoter(char **line);
void				dequoter(t_env_list **env, char **line);
void				set_quote(char *quote, char c);

/* piper.c */
void				piper(char **line);

/* spacer.c */
void				spacer(char **line);

/* expander.c */
void				expander(t_env_list **env, char **line, int *i);

/* lexer.c */
t_list				*lexer(t_env_list **env, char *line);

/* checker.c a*/
int					is_syntax_cmd(t_list *token_lst);

/* parser.c */
void				parser(t_list **token_lst, t_shell_info *info);

/* str_utils.c */
void				add_substr(char **str, int start, char *substr);
void				rm_substr(char **str, int start, int len);

/* execute_binary.c */
int					run_binary(int cmd_num, t_shell_info *info);

/* execute.c */
void				executor(t_shell_info *info);

/*parser_utils.c*/
int					lst_cnt(char *str, t_list *token_lst);
int					count_cmd(t_list *token_lst);
int					token_count(t_list *token_lst);
t_simple_command	*pipe_cut(t_list *temp, t_simple_command *pipes, \
						t_shell_info *info);

/* here_doc.c*/
int					write_to_heredoc(t_shell_info *info);
#endif
