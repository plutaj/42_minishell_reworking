/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handeling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:58:31 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/17 17:02:01 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_operator(char *s, t_parser *st)
{
	if ((s[st->i] == '<' && s[st->i + 1] == '<') || (s[st->i] == '>' && s[st->i
				+ 1] == '>'))
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
}

int	handle_redirections(char *s, t_parser *st)
{
	if (s[st->i] == '<' || s[st->i] == '>')
	{
		flush_buffer(st);
		parse_operator(s, st);
		while (s[st->i] == ' ')
			st->i++;
		st->buf_i = 0;
		while (s[st->i] && s[st->i] != ' ' && s[st->i] != '<'
			&& s[st->i] != '>')
			st->buffer[st->buf_i++] = s[st->i++];
		st->args[(st->j)] = ft_strdup(st->buffer);
		// if (!(st->args[(st->j)])) // added malloc protec (update, not working)
		// 	return (0);			// added malloc protec (update, not working)
		return (1);
	}
	return (0);
}

void	handle_quotes(char c, char *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (!(*quote))
			*quote = c;
		else if (*quote == c)
			*quote = 0;
	}
}
