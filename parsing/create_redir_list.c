/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:06:39 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/09 16:51:31 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	t_command *cmd_list = data->cmd_list;

	while (cmd_list)
	{
		process_command_redirs(cmd_list);
		cmd_list = cmd_list->next;
	}
}

void	process_command_redirs(t_command *cmd)
{
	int	i;
	int j;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (check_for_redir(cmd->args[i]))
		{
			add_redir_node(&(cmd->args[i]), cmd);
			free(cmd->args[i]);
			if (cmd->args[i + 1])
				free(cmd->args[i + 1]);
			
			j = i;
			while (cmd->args[j + 2])
			{
				cmd->args[j] = cmd->args[j + 2];
				j++;
			}
			cmd->args[j] = NULL;
			cmd->args[j + 1] = NULL;
			continue;
		}
		i++;
	}
}

t_redir	*create_redir_node(char **args)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);

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
	return (new_redir);
}

void	add_redir_node(char **args, t_command *cmd_list)
{
	t_redir	*new_redir;
	t_redir	*temp_redir;

	new_redir = create_redir_node(args);
	if (!new_redir)
		return ;

	if (!cmd_list->redir)
		cmd_list->redir = new_redir;
	else
	{
		temp_redir = cmd_list->redir;
		while (temp_redir->next)
			temp_redir = temp_redir->next;
		temp_redir->next = new_redir;
	}
}
