/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list_utils2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:53:21 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/19 20:54:54 by jozefpluta       ###   ########.fr       */
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
			// if (!st->args[st->j++]) // added malloc protec (update, not working)
			// 	return (0);			// added malloc protec (update, not working)
			st->buf_i = 0;
		}
		st->i++;
		return (1);
	}
	return (0);
}

void append_command_to_list(t_data *data, t_command *new_cmd, t_command **temp_cmd)
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
		free(args[i]);
		args[i] = cleaned;
		i++;
	}
}
