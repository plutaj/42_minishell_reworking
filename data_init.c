/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:22:09 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/20 17:19:28 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->env = copy_envp(envp); // set a env var 2d array
	data->input = NULL;
	get_path(data); // set a current path in data struct
	data->cmd_list = NULL;
	data->is_single = 0;
	data->is_double = 0;
}
	
void	get_path(t_data *data)
{
	char	*cwd;
    char	buffer[1024];

    cwd = getcwd(buffer, sizeof(buffer));
    if (cwd == NULL)
	{
		perror("getcwd() error");
		exit(1);
	}
	// if (data->current_path)
	// 	free(data->current_path);
	data->current_path = ft_strdup(cwd);
	update_env_var(data->env, "PWD", cwd);
}

void	set_data_to_default(t_data *data)
{
	t_command	*temp;

	temp = data->cmd_list;
	while (data->cmd_list)
	{
		temp = data->cmd_list->next;
		free(data->cmd_list);
		data->cmd_list = temp;
	}
	data->cmd_list = NULL;
	if (data->input)
	{
		free (data->input);
		data->input = NULL;
	}
}