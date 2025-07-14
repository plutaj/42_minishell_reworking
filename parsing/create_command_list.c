/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:08:56 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/14 17:02:48 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_command_list(t_data *data)
{
	char		**s;
	int			i;
	t_command	*new_cmd;
	t_command	*temp_cmd;

	s = ft_split_quote_aware(data->input, '|');
	i = 0;
	while (s[i])
	{
		new_cmd = (t_command *)malloc(sizeof(t_command));
		new_cmd->args = NULL;
		new_cmd->redir = NULL;
		new_cmd->data = data;
		new_cmd->next = NULL;
		new_cmd = split_args_and_redirs(s[i], new_cmd);
		find_variables(new_cmd);
		remove_quotes_from_args(new_cmd->args);
		if (!data->cmd_list)
			data->cmd_list = new_cmd;
		else
			temp_cmd->next = new_cmd;
		temp_cmd = new_cmd;
		i++;
	}
	free_2d_array(s);
}

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

void	flush_buffer(t_parser *st)
{
	if (st->buf_i > 0)
	{
		st->buffer[st->buf_i] = '\0';
		st->args[st->j++] = ft_strdup(st->buffer);
	}
}

t_command	*split_args_and_redirs(char *string, t_command *new_cmd)
{
	t_parser	st;
	char		quote;

	st.args = ft_calloc(256, sizeof(char *));
	st.i = 0;
	st.j = 0;
	st.buf_i = 0;
	quote = 0;
	while (string[st.i])
	{
		handle_quotes(string[st.i], &quote);
		if (!quote && handle_redirections(string, &st))
			continue ;
		if (!quote && handle_spaces(string, &st))
			continue ;
		st.buffer[st.buf_i++] = string[st.i++];
	}
	flush_buffer(&st);
	st.args[st.j] = NULL;
	new_cmd->args = st.args;
	return (new_cmd);
}

void	remove_quotes_from_args(char **args)
{
	int		i;
	char	*cleaned;

	i = 0;
	while (args[i])
	{
		cleaned = remove_quotes(args[i]);
		free(args[i]);
		args[i] = cleaned;
		i++;
	}
}
