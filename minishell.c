/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:04:27 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/29 20:03:16 by jozefpluta       ###   ########.fr       */
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
	// Initializing all data like PATH, ENV and so ... rest to NULL
	init_data(&data, envp);
	while (1)
	{
		data.input = readline("minishell$ ");
		if (data.input)
			add_history(data.input);
		edge_cases(&data);
		init_cmd_list(&data);
	}
    return (0);
}

void	init_redir_list(t_data *data)
{
	t_command	*temp;

	temp = data->cmd_list;
	while (temp)
	{
		
		temp = temp->next;
	}
}

void	init_cmd_redir_list(t_data *data)
{
	char 		**s;
	t_command	*new;
	t_command	*temp;
	
	s = ft_split(data->input, '|');
	new = NULL;
	temp = data->cmd_list;
	while (*s)
	{
		if (!temp)
		{
			temp = (t_command *)malloc(sizeof(t_command));
			// temp->args = ft_split(*s, ' ');
			temp->redir = NULL;
			split_args_and_redirs(temp, *s);
			temp->next = NULL;
			data->cmd_list = temp;
		}
		else
		{
			new = (t_command *)malloc(sizeof(t_command));
			// new->args = ft_split(*s, ' ');
			new->redir = NULL;
			split_args_and_redirs(new, *s);
			new->next = NULL;
			temp->next = new;
			temp = temp->next;
			new = NULL;
		}
		s++;
	}
}

void	split_args_and_redirs(t_command *cmd_list, char *s)
{
	char	**temp;
	int		i;

	temp = ft_split(s, ' ');
	i = 0;
	while (temp[i])
	{
		if (ft_strcmp(temp[i], "<") == 0 && temp[i + 1])
		{
			init_redir_list(cmd_list->redir, REDIR_INPUT, temp[i + 1]);
			i += 2;
		}
		else if (ft_strcmp(temp[i], ">") == 0 && temp[i + 1])
		{
			init_redir_list(cmd_list->redir, REDIR_OUTPUT, temp[i + 1]);
			i += 2;
		}
		else
		{
			cmd_list->args[arg_index++] = ft_strdup(temp[i]);
			i++;
		}
	}
	cmd_list->args[arg_index] = NULL;
}

void	init_redir_list(t_redir *redir, t_redir_type type, char *str)
{
	if (!redir)
	{
		redir = (t_redir *)malloc(sizeof(t_redir));
		redir->type = type;
		redir->file_or_limiter = ft_strdup(str);
		redir->next = NULL;
	}
	else
	{
		while (redir->next)
			redir = redir->next;
		redir->next = (t_redir *)malloc(sizeof(t_redir));
		redir->next->type = type;
		redir->next->file_or_limiter = ft_strdup(str);
		redir = redir->next;
		redir->next = NULL;
	}
}