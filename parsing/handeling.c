/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handeling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:58:31 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/28 16:14:36 by huahmad          ###   ########.fr       */
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

// int	handle_redirections(char *s, t_parser *st)
// {
// 	if (s[st->i] == '<' || s[st->i] == '>')
// 	{
// 		flush_buffer(st);
// 		parse_operator(s, st);
// 		while (s[st->i] == ' ')
// 			st->i++;
// 		st->buf_i = 0;
// 		while (s[st->i] && s[st->i] != ' ' && s[st->i] != '<'
// 			&& s[st->i] != '>')
// 			st->buffer[st->buf_i++] = s[st->i++];
// 		st->buffer[st->buf_i] = '\0';
// 		if (st->args[st->j])
// 			free(st->args[st->j]);
// 		if (!st->args[st->j])
// 			return (0);
// 		return (1);
// 	}
// 	return (0);
// }

static int	parse_redirection_target(char *s, t_parser *st)
{
	char quote = 0;

	while (s[st->i])
	{
		if (!quote && (s[st->i] == '\'' || s[st->i] == '"'))
			quote = s[st->i++];
		else if (quote && s[st->i] == quote)
		{
			quote = 0;
			st->buffer[st->buf_i++] = s[st->i++];
		}
		else if (!quote && (s[st->i] == ' ' || s[st->i] == '<' || s[st->i] == '>'))
			break;
		else
			st->buffer[st->buf_i++] = s[st->i++];
	}
	st->buffer[st->buf_i] = '\0';
	if (st->args[st->j])
		free(st->args[st->j]);
	return (st->args[st->j] != NULL);
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
		return parse_redirection_target(s, st);
	}
	return 0;
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

void	var_and_quote_handling(t_command *new_cmd)
{
	find_variables(new_cmd);
	remove_quotes_from_args(new_cmd->args);
}

int	is_valid_redirection(char **args)
{
	if (!args || !args[0] || !args[1])
		return (0);
	if (!ft_strcmp(args[0], "<")
		|| !ft_strcmp(args[0], ">>")
		|| !ft_strcmp(args[0], ">")
		|| !ft_strcmp(args[0], "<<"))
	{
		if (args[1][0] == '<' || args[1][0] == '>')
			return (0);
		return (1);
	}
	return (0);
}
