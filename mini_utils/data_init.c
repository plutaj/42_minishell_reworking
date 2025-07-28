/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:22:09 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/28 13:37:01 by huahmad          ###   ########.fr       */
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
	if (!data)
		return ;
	free_command_list(data->cmd_list);
	data->cmd_list = NULL;
	if (data->input)
		free(data->input);
	data->input = NULL;
	// if (data->current_path)
	// 	free(data->current_path);
	// data->current_path = NULL;
}

void	free_command_list(t_command *cmd_list)
{
	t_command	*temp_cmd;
	t_redir		*redir;
	t_redir		*next_redir;

	while (cmd_list)
	{
		redir = cmd_list->redir;
		while (redir)
		{
			next_redir = redir->next;
			free(redir->file_or_limiter);
			free(redir);
			redir = next_redir;
		}
		free_2d_array(cmd_list->args);
		temp_cmd = cmd_list->next;
		free(cmd_list);
		cmd_list = temp_cmd;
	}
}
