/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:06:39 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/28 11:32:35 by jpluta           ###   ########.fr       */
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

// int	check_for_redir(char *arg)
// {
// 	if (ft_strncmp(arg, "<", 1) == 0)
// 		return (1);
// 	else if (ft_strncmp(arg, ">", 1) == 0)
// 		return (1);
// 	else if (ft_strncmp(arg, "<<", 2) == 0)
// 		return (1);
// 	else if (ft_strncmp(arg, ">>", 2) == 0)
// 		return (1);
// 	return (0);
// }

void	create_redir_list(t_data *data)
{
	t_command	*cmd_list;
	int			i;
	int			x;
	
	cmd_list = data->cmd_list;
	i = 0;
	while (cmd_list)
	{
		while (cmd_list->args && cmd_list->args[i])
		{
			if (check_for_redir(cmd_list->args[i]))
			{
				add_redir_node(&(cmd_list->args[i]), cmd_list);
				x = i;
				while (cmd_list->args[x])
					free(cmd_list->args[x++]);
				cmd_list->args[i] = NULL;
				continue ;
			}
			i++;
		}
		i = 0;
		cmd_list = cmd_list->next;
	}
}

// void	add_redir_node(char **args, t_command *cmd_list)
// {
// 	t_redir *new_redir;
// 	t_redir *temp_redir;
// 	int		i;

// 	new_redir = (t_redir *)malloc(sizeof(t_redir));
// 	i = 0;
// 	if (ft_strncmp(args[0], "<", 1) == 0)
// 	{
// 		new_redir->type = REDIR_INPUT;
// 		i = 1;
// 	}
// 	else if (ft_strncmp(args[0], ">", 1) == 0)
// 	{
// 		new_redir->type = REDIR_OUTPUT;
// 		i = 1;
// 	}
// 	else if (ft_strncmp(args[0], ">>", 2) == 0)
// 	{
// 		new_redir->type = REDIR_APPEND;
// 		i = 2;
// 	}
// 	else if (ft_strncmp(args[0], "<<", 2) == 0)
// 	{
// 		new_redir->type = REDIR_HEREDOC;
// 		i = 2;
// 	}
// 	if (!args[0][i])
// 	{
// 		if (args[1])
// 			new_redir->file_or_limiter = ft_strdup(args[1]);
// 		else
// 			new_redir->file_or_limiter = NULL;
// 	}
// 	else
// 	{
// 		if (args[0][i])
// 			new_redir->file_or_limiter = ft_strdup(&(args[0][i]));
// 		else
// 			new_redir->file_or_limiter = NULL;
// 	}
// 	new_redir->next = NULL;
// 	if (!cmd_list->redir)
//     	cmd_list->redir = new_redir;
// 	else
// 	{
// 	    temp_redir = cmd_list->redir;
// 	    while (temp_redir->next)
// 	        temp_redir = temp_redir->next;
// 	    temp_redir->next = new_redir;
// 	}
// }

void	add_redir_node(char **args, t_command *cmd_list)
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
