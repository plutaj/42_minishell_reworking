/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:06:39 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/10 10:53:56 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_for_redir(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '<' && arg[i + 1] == '<')
			return (&arg[i]);
		else if (arg[i] == '>' && arg[i + 1] == '>')
			return (&arg[i]);
		else if (arg[i] == '<')
			return (&arg[i]);
		else if (arg[i] == '>')
			return (&arg[i]);
		i++;
	}
	return (NULL);
}

void	create_redir_list(t_data *data)
{
	int		i;
	char	*p_to_redir;
	char	*temp;

	i = 0;
	while (data->commands->args[i])
	{
		if ((p_to_redir = check_for_redir(data->commands->args[i])) != NULL)
		{
			add_redir_node(p_to_redir, data);
			*p_to_redir = '\0';
			temp = ft_strdup(data->commands->args[i]);
			free(data->commands->args[i]);
			data->commands->args[i] = temp;
			continue ;
		}
		i++;
	}
}

void	add_redir_node(char *p_to_redir, t_data *data)
{
	t_redir *new_redir;
	t_redir *temp_redir;
	int		i;

	i = 0;
	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (p_to_redir[i] == '<' && p_to_redir[i + 1] == '<')
		new_redir->type = REDIR_HEREDOC;
	else if (p_to_redir[i] == '>' && p_to_redir[i + 1] == '>')
		new_redir->type = REDIR_APPEND;
	else if (p_to_redir[i] == '<')
		new_redir->type = REDIR_INPUT;
	else if (p_to_redir[i] == '>')
		new_redir->type = REDIR_OUTPUT;
	if (new_redir->type == 2 || new_redir->type == 3)
		i += 2;
	else
		i += 1;
	while (*p_to_redir && p_to_redir[i] == ' ')
		i++;
	if (p_to_redir[i])
		new_redir->file_or_limiter = ft_strdup(&p_to_redir[i]);
	else
		new_redir->file_or_limiter = NULL;
	new_redir->next = NULL;
	if (!data->commands->redir)
		data->commands->redir = new_redir;
	else
	{
		temp_redir = data->commands->redir;
		while (temp_redir->next)
			temp_redir = temp_redir->next;
		temp_redir->next = new_redir;
	}
}