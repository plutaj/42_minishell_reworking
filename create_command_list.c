/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:08:56 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/09 16:41:47 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_command_list(t_data *data)
{
	char		**s;
	t_command	*new_cmd;

	new_cmd = NULL;
	s = ft_split(data->input, '|');
	if (!s)
		return ;
	cut_spaces(s);
	new_cmd = (t_command *)malloc(sizeof(t_command));
	if (!new_cmd)
		return ;
	new_cmd->redir = NULL;
	new_cmd->args = s;
	data->commands = new_cmd;
}

void	cut_spaces(char **s)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j] == ' ' || s[i][j] == '\t')
			j++;
		trimmed = strdup(s[i] + j);
		free(s[i]);
		s[i] = trimmed;
		i++;
	}
}
