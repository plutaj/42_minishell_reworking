/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:22:09 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/21 17:40:31 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->env = copy_envp(envp);
	if (!data->env)
		return ;
	data->input = NULL;
	get_path(data);
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
		g_last_exit_status = 1;
		exit(1);
	}
	data->current_path = ft_strdup(cwd);
	update_env_var(data->env, "PWD", cwd);
	g_last_exit_status = 0;
}

void	set_data_to_default(t_data *data)
{
	t_command	*temp;
	t_redir		*r_temp;

	temp = data->cmd_list;
	while (data->cmd_list)
	{
		if (data->cmd_list->redir)
		{
			if (data->cmd_list->redir->file_or_limiter)
				free(data->cmd_list->redir->file_or_limiter);
			r_temp = data->cmd_list->redir->next;
			free(data->cmd_list->redir);
			data->cmd_list->redir = r_temp;
		}
		free_2d_array(data->cmd_list->args);
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
