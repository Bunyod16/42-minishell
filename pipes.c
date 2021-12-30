/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:43:20 by bunyodshams       #+#    #+#             */
/*   Updated: 2021/12/31 02:02:22 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft/libft.h"
#include <stdlib.h>

int spec_char_num(char *line)
{
    int i;
    int count;

    count = 0;
    i = -1;
    while (line[++i])
    {
        if (line[i] == '|')
            count++;
        else if (line[i] == '>')
        {
            if (line[i + 1] == '>')
                i++;
            count++;
        }
        else if (line[i] == '<')
        {
            if (line[i + 1] == '<')
                i++;
            count++;
        }
    }
    return (count);
}

int is_special_char(char *str, int i)
{
	const char	c1 = str[i];
	const char	c2 = str[i + 1];

	if ((c1 == '>' && c2 == '>') || (c1 == '<' && c2 == '<'))
		return (2);
    if (c1 == '|' || c1 == '>' || c1 == '<')
        return (1);
    return (0);
}

void    init_token(t_token *token)
{
    token->input_fd = 0;
	token->input_redir = 0;
	token->input_eof = 0;
    token->output_fd = 0;
	token->output_pipe = 0;
	token->output_append = 0;
	token->output_redir = 0;
	token->cmd = 0;
    token->str = 0;
}

/* removes spaces in the line */
char	*clean_line(char *line)
{
    int         i;
    const int   len = ft_strlen(line);

    i = -1;
    while (line[++i])
    {
        if (is_special_char(line, i))
        {
            if (i != 0 && line[i - 1] == ' ')
			{
                ft_strlcpy(&line[i - 1], &line[i], len);
				i--;
			}
            if (i != 0 && line[i + 1] == ' ')
                ft_strlcpy(&line[i + 1], &line[i + 2], len);
        }
    }
	return (line);
}

/* adds the .cmd string to the token */
t_token	*process_cmd(t_token *tokens)
{
	int i;

	i = -1;
	printf("|%s|",tokens[0].str);
	while (tokens[++i].str)
	{
		if (ft_strncmp(tokens[i].cmd, "|", 1))
			tokens[i].output_pipe = 1;
		else if (ft_strncmp(tokens[i].cmd, "<<", 2))
			tokens[i].input_eof = 1;
		else if (ft_strncmp(tokens[i].cmd, ">>", 2))
			tokens[i].output_append = 1;
		else if (ft_strncmp(tokens[i].cmd, ">", 1))
			tokens[i].output_redir = 1;
		else if (ft_strncmp(tokens[i].cmd, "<", 1))
			tokens[i].input_redir = 1;		
	}
	return (tokens);
}

t_token *generate_tokens(char *line)
{
    t_token     *tokens = malloc(sizeof(t_token) * spec_char_num(line) + 1);
    int         i;
    int         tok_num;
    int         last_cmd;

    last_cmd = 0;
    tok_num = 0;
    i = -1;
    while (line[++i])
    {
        if (is_special_char(line, i) > 0 || line[i + 1] == 0)
        {
			init_token(&tokens[tok_num]);
			if (line[i + 1] == 0)
				tokens[tok_num].str = ft_substr(line, last_cmd, i - ft_strlen(line));
			else
			{
            	tokens[tok_num].str = ft_substr(line, last_cmd, i - last_cmd);
				tokens[tok_num].cmd = ft_substr(line, i, is_special_char(line, i));
			}
			printf("|%s|\n",tokens[tok_num].str);
			i += is_special_char(line, i);
            tok_num++;
            last_cmd = i;
        }
    }
    return (tokens);
}
