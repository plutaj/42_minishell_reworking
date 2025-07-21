/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:08:56 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/21 17:52:58 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*set_new_node_to_def(t_command *new_cmd, t_data *data);
void		var_and_quote_handling(t_command *new_cmd);

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
			return ; 
		var_and_quote_handling(new_cmd);
		append_command_to_list(data, new_cmd, &temp_cmd);  
		i++;
	}
	free_2d_array(s);
}

void	var_and_quote_handling(t_command *new_cmd)
{
	find_variables(new_cmd);
	remove_quotes_from_args(new_cmd->args);
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

	st.args = ft_calloc(256, sizeof(char *));
	if (!st.args)
	{
		free(new_cmd);
		return (NULL);
	}
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

// void	create_command_list(t_data *data)
// {
// 	char		**s;
// 	int			i;
// 	t_command	*new_cmd;
// 	t_command	*temp_cmd;

// 	s = ft_split_quote_aware(data->input, '|');
// 	i = 0;
// 	while (s[i])
// 	{
// 		new_cmd = (t_command *)malloc(sizeof(t_command));
// 		new_cmd->args = NULL;
// 		new_cmd->redir = NULL;
// 		new_cmd->data = data;
// 		new_cmd->next = NULL;
// 		new_cmd = split_args_and_redirs(s[i], new_cmd);
// 		find_variables(new_cmd);
// 		remove_quotes_from_args(new_cmd->args);
// 		if (!data->cmd_list)
// 			data->cmd_list = new_cmd;
// 		else
// 			temp_cmd->next = new_cmd;
// 		temp_cmd = new_cmd;
// 		i++;
// 	}
// 	free_2d_array(s);
// }
