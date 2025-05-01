/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:04:27 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/01 17:05:56 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!check_for_quotes(&data));
			exit(1); // handle this like not correct pair of quotes
		create_comand_list(&data);
	}
    return (0);
}

void create_command_list(t_data *data)
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
	// Free s after
}

void	split_args_and_redirs(t_data *data, t_command *new_cmd, char *s)
{
	char	**new_s;
	int		i;
	int		arg_i;
	char	ch;
	int		len;

	new_s = ft_split(s, ' ');
	i = 0;
	arg_i = 0;
	ch = NULL;
	new_cmd->args = (char **)malloc(sizeof(char *) * 254);
	while (new_s[i])
	{
		if ((len = get_index_of_quotes(new_s[i], data)))
		{
			new_s[i][len] = '\0';
			new_cmd->args[arg_i] = ft_strdup(new_s[i]);
			arg_i++;
			len++;
			// if (new_s[i][len])
			// 	new_cmd->args[arg_i] = ft_strdup(&(new_s[i][len])); tu som skoncil
		}
		else
		{
			new_cmd->args[arg_i] = ft_strdup(new_s[i]);
			arg_i++;
		}
		i++;
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