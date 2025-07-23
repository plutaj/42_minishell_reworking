/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:08:56 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/23 17:10:08 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_command_list_error(t_data *data, char **s)
{
	free_command_list(data->cmd_list);
	data->cmd_list = NULL;
	free_2d_array(s);
}

void	create_command_list(t_data *data)
{
	char		**s;
	int			i;
	t_command	*new_cmd;
	t_command	*temp_cmd;

	s = ft_split_quote_aware(data->input, '|');
	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		new_cmd = set_new_node_to_def(new_cmd, data);
		if (!new_cmd)
			break ;
		new_cmd = split_args_and_redirs(s[i], new_cmd);
		if (!new_cmd)
		{
			handle_command_list_error(data, s);
			return ;
		}
		var_and_quote_handling(new_cmd);
		append_command_to_list(data, new_cmd, &temp_cmd);
		i++;
	}
	free_2d_array(s);
}

t_command	*set_new_node_to_def(t_command *new_cmd, t_data *data)
{
	new_cmd = (t_command *)malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->redir = NULL;
	new_cmd->data = data;
	new_cmd->next = NULL;
	new_cmd->parseerror = 0;
	return (new_cmd);
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

	quote = 0;
	if (!init_parser_state(&st, new_cmd))
		return (NULL);
	parse_input_string(string, &st, &quote);
	flush_buffer(&st);
	if (!st.args)
	{
		free(new_cmd);
		return (NULL);
	}
	st.args[st.j] = NULL;
	new_cmd->args = st.args;
	return (new_cmd);
}
