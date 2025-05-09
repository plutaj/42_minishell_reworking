/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:06:39 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/09 16:45:31 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_redir(char *arg)
{
	if (ft_strcmp(arg, "<") == 0)
		return (1);
	else if (ft_strcmp(arg, ">") == 0)
		return (1);
	else if (ft_strcmp(arg, "<<") == 0)
		return (1);
	else if (ft_strcmp(arg, ">>") == 0)
		return (1);
	return (0);
}

void	create_redir_list(t_data *data)
{
	t_command	*commands = data->commands;
	int			i, j;

	i = 0;
		while (commands->args && commands->args[i])
		{
			if (check_for_redir(commands->args[i]))
			{
				add_redir_node(&(commands->args[i]), commands);
				free(commands->args[i]);
				if (commands->args[i + 1])
					free(commands->args[i + 1]);
				j = i;
				while (commands->args[j + 2])
				{
					commands->args[j] = commands->args[j + 2];
					j++;
				}
				commands->args[j] = NULL;
				commands->args[j + 1] = NULL;
				continue ;
			}
			i++;
		}
}

// void	create_redir_list(t_data *data)
// {
// 	t_command	*commands;
// 	int			i;
// 	int			x;
	
// 	commands = data->commands;
// 	i = 0;
// 	while (commands->args && commands->args[i])
// 	{
// 		if (check_for_redir(commands->args[i]))
// 		{
// 			add_redir_node(&(commands->args[i]), commands);
// 			x = i;
// 			while (commands->args[x])
// 				free(commands->args[x++]);
// 			commands->args[i] = NULL;
// 			continue ;
// 		}
// 		i++;
// 	}
// }

void	add_redir_node(char **args, t_command *commands)
{
	t_redir *new_redir;
	t_redir *temp_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (ft_strcmp(args[0], "<") == 0)
		new_redir->type = REDIR_INPUT;
	else if (ft_strcmp(args[0], ">") == 0)
		new_redir->type = REDIR_OUTPUT;
	else if (ft_strcmp(args[0], ">>") == 0)
		new_redir->type = REDIR_APPEND;
	else if (ft_strcmp(args[0], "<<") == 0)
		new_redir->type = REDIR_HEREDOC;
	if (args[1])
		new_redir->file_or_limiter = ft_strdup(args[1]);
	else
		new_redir->file_or_limiter = NULL;
	new_redir->next = NULL;
	if (!commands->redir)
		commands->redir = new_redir;
	else
	{
		temp_redir = commands->redir;
		while (temp_redir->next)
			temp_redir = temp_redir->next;
		temp_redir->next = new_redir;
	}
}