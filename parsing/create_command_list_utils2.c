/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list_utils2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:53:21 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/28 16:02:56 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_spaces(char *s, t_parser *st)
{
	if (s[st->i] == ' ')
	{
		if (st->buf_i > 0)
		{
			st->buffer[st->buf_i] = '\0';
			st->args[st->j++] = ft_strdup(st->buffer);
			st->buf_i = 0;
		}
		st->i++;
		return (1);
	}
	return (0);
}

void	append_command_to_list(t_data *data, t_command *new_cmd,
		t_command **temp_cmd)
{
	if (!data->cmd_list)
		data->cmd_list = new_cmd;
	else
		(*temp_cmd)->next = new_cmd;
	*temp_cmd = new_cmd;
}

void	remove_quotes_from_args(char **args)
{
	int		i;
	char	*cleaned;

	i = 0;
	while (args[i])
	{
		cleaned = remove_quotes(args[i]);
		if (cleaned)
		{
			free(args[i]);
			args[i] = cleaned;
		}
		i++;
	}
}

int	init_parser_state(t_parser *st, t_command *new_cmd)
{
	st->args = ft_calloc(256, sizeof(char *));
	if (!st->args)
	{
		free(new_cmd);
		return (0);
	}
	st->i = 0;
	st->j = 0;
	st->buf_i = 0;
	return (1);
}

void	parse_input_string(char *string, t_parser *st, char *quote)
{
	while (string[st->i])
	{
		handle_quotes(string[st->i], quote);
		if (!(*quote) && handle_redirections(string, st))
			continue ;
		if (!(*quote) && handle_spaces(string, st))
			continue ;
		if (string[st->i])
			st->buffer[st->buf_i++] = string[st->i++];
	}
}
