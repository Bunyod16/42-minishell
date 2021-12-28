/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:43:20 by bunyodshams       #+#    #+#             */
/*   Updated: 2021/12/28 19:27:16 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "libft/libft.h"
#include <stdlib.h>

int count_special_chars(char *line)
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

int is_special_char(char c)
{
    if (c == '|' || c == '>' || c == '<')
        return (1);
    return (0);
}

void    init_token(t_token *token)
{
    token->input_fd = 0;
    token->output_fd = 0;
	token->append_output = 0;
	token->redir_input = 0;
	token->redir_output = 0;
    token->str = 0;
}

void    clean_line(char *line)
{
    int         i;
    const int   len = ft_strlen(line);

    i = -1;
    while (line[++i])
    {
        if (is_special_char(line[i]))
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
}

t_token *generate_tokens(char *line)
{
    const int   special_chars = count_special_chars(line);
    t_token     *tokens = malloc(sizeof(t_token) * special_chars);
    t_token     token;
    int         i;
    int         tok_num;
    int         last_cmd;

    last_cmd = 0;
    tok_num = 0;
    i = -1;
    clean_line(line);
    printf("%s\n",line);
    while (line[++i])
    {
        if (is_special_char(line[i]) || line[i + 1] == 0)
        {
            init_token(&token);
            token.str = ft_substr(line, last_cmd, i - last_cmd);
			i++;
            printf("%s\n",token.str);
            tokens[tok_num] = token;
            tok_num++;
            last_cmd = i;
        }
    }
    return (tokens);
}
