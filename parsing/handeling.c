/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handeling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:58:31 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/09 17:44:08 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_redirections(char *s, t_parser *st)
{
	if (s[st->i] == '<' || s[st->i] == '>')
	{
		flush_buffer(st);
		if ((s[st->i] == '<' && s[st->i + 1] == '<') || (s[st->i] == '>' && s[st->i + 1] == '>'))
		{
			st->buffer[0] = s[st->i];
			st->buffer[1] = s[st->i + 1];
			st->buffer[2] = '\0';
			st->args[st->j++] = ft_strdup(st->buffer);
			(st->i) += 2;
		}
		else
		{
			st->buffer[0] = s[st->i];
			st->buffer[1] = '\0';
			st->args[(st->j)++] = ft_strdup(st->buffer);
			(st->i)++;
		}
		st->buf_i = 0;
		while (s[st->i] && s[st->i] != ' ' && s[st->i] != '<' && s[st->i] != '>')
			st->buffer[st->buf_i++] = s[st->i++];
		st->args[(st->j)] = ft_strdup(st->buffer);
		return (1);
	}
	return (0);
}

void	handle_quotes(char c, char *quote)
{
	if (c =='\'' || c == '\"')
	{
		if (!(*quote))
			*quote = c;
		else if (*quote == c)
			*quote = 0; 
	}
}
