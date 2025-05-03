/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:04:27 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/03 13:23:41 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* printing purposes */
void	print_linked_list(t_command *cmd_list)
{	
	int	i;
	int node;

	i = 0;
	node = 0;
	while (cmd_list)
	{
		if (cmd_list->args[i])
				printf("%d ARGS: ", node);
		while (cmd_list->args[i])
		{
			printf("%s ", cmd_list->args[i]);
			i++;
		}
		if (cmd_list->redir)
			printf("%d REDIRS: ", node);
		while (cmd_list->redir)
		{
			printf("TYPE %u %s", cmd_list->redir->type, cmd_list->redir->file_or_limiter);
			cmd_list->redir = cmd_list->redir->next;
		}
		printf("\n");
		i = 0;
		node++;
		cmd_list = cmd_list->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void)argc;
	(void)argv;
	if (argc != 1)
		return (printf("Error: Unexpected input.\n"));
	init_data(&data, envp);
	while (1)
	{
		data.input = readline("minishell$ ");
		if (data.input)
			add_history(data.input);
		if (!(check_for_quotes(&data)))
		{
			printf("Wrong number of quotes\n");
			exit(1); // handle this like not correct pair of quotes
		}
		create_command_list(&data);
		print_linked_list(data.cmd_list);
		set_data_to_default(&data);
	}
    return (0);
}

void	create_command_list(t_data *data)
{
	char		**s;
	int			i;
	t_command	*new_cmd;
	t_command	*temp_cmd;

	s = ft_split(data->input, '|');
	i = 0;
	while (s[i])
	{
		new_cmd = (t_command *)malloc(sizeof(t_command));
		new_cmd->args = NULL;
		new_cmd->redir = NULL;
		new_cmd->next = NULL;
		split_args_and_redirs(data, new_cmd, s[i]);
		if (!data->cmd_list)
			data->cmd_list = new_cmd;
		else
			temp_cmd->next = new_cmd;
		temp_cmd = new_cmd;
		i++;
	}
	free_2d_array(s);
}

void	split_args_and_redirs(t_data *data, t_command *new_cmd, char *s)
{
	char	**new_s;
	int		i;
	int		arg_i;
	int		len;

	new_s = ft_split(s, ' ');
	i = 0;
	arg_i = 0;
	new_cmd->args = (char **)malloc(sizeof(char *) * 254);
	while (new_s[i])
	{
		if ((len = get_index_of_quotes(new_s[i], data)))
		{
			new_s[i][len] = '\0';
			new_cmd->args[arg_i] = ft_strdup(new_s[i]);
			arg_i++;
			len++;
			if (new_s[i][len])
			{
				new_cmd->arg_i = arg_i;
				copy_string_till_quotes(data, new_s, &i, &len);// cpy till single or double quotes (depend on whats 1 in data structure is true)
				arg_i = new_cmd->arg_i;
			}
		}
		else
		{
			new_cmd->args[arg_i] = ft_strdup(new_s[i]);
			arg_i++;
		}
		i++;
	}
	new_cmd->args[arg_i++] = NULL; // otazne
	free_2d_array(new_s);
}

void	copy_string_till_quotes(t_data *data, char **new_s, int *i, int *len)
{
	char	quote;
	char	*start;
	
	start = &(new_s[*i][*len]);
	if (data->is_single)
		quote = '\'';
	else if (data->is_double)
		quote = '\"';
	else
		printf("____mistake in copy_string_till_quotes______");
	while (new_s[*i])
	{
		while (new_s[*i][*len])
		{
			if (new_s[*i][*len] == quote)
			{
				// maybe needed to handle the case if quotes continues to another row
				new_s[*i][*len] = '\0';
				data->cmd_list->args[data->cmd_list->arg_i] = ft_strdup(start);
				if (quote == '\'')
					data->is_single = 0;
				else if (quote == '\"')
					data->is_double = 0;
			}
			*len += 1;
		}
		*i += 1;
	}
}

int	get_index_of_quotes(char *s, t_data *data)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			data->is_single = 1;
			return (i);
		}
		else if (s[i] == '\"')
		{
			data->is_double = 1;
			return (i);
		}
		i++;
	}
	return (0);
}