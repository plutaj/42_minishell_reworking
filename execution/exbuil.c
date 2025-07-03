/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exbuil.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:07:29 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/03 17:13:30 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_command *cmd_list)
{
	if (cmd_list == NULL || cmd_list->args == NULL || cmd_list->args[0] == NULL)
		return (0);
	if (ft_strcmp("echo", cmd_list->args[0]) == 0)
		return (1);
	else if (ft_strcmp("cd", cmd_list->args[0]) == 0)
		return (1);
	else if (ft_strcmp("pwd", cmd_list->args[0]) == 0)
		return (1);
	else if (ft_strcmp("export", cmd_list->args[0]) == 0)
		return (1);
	else if (ft_strcmp("unset", cmd_list->args[0]) == 0)
		return (1);
	else if (ft_strcmp("env", cmd_list->args[0]) == 0)
		return (1);
	else if (ft_strcmp("exit", cmd_list->args[0]) == 0)
		return (1);
	else if (ft_strcmp("export", cmd_list->args[0]) == 0)
		return (1);
	return (0);
}

char	*search_command_in_path(t_command *cmd_list, t_data *data)
{
	char	*path;

	path = is_env_var("$PATH", data->env); // this 
	if (path && *path != '\0')
		return (find_command_in_path(cmd_list->args[0]));
	return (NULL);
}

void	is_external(t_data *data, t_command *cmd_list)
{
	char	*result;

	result = NULL;
	if (ft_strchr(cmd_list->args[0], '/'))
	{
		if (access(cmd_list->args[0], X_OK) == 0)
		{
			execute_command(cmd_list->args[0], cmd_list->args, data->env);
			return ;
		}
	}
	else
		result = search_command_in_path(cmd_list, data);
	if (result)
	{
		execute_command(result, cmd_list->args, data->env);
		free(result);
	}
	else
	{
		write(1, "command not found: ", 19);
		write(1, cmd_list->args[0], ft_strlen(cmd_list->args[0]));
		write(1, "\n", 2);
		g_last_exit_status = 127;
	}
}

void	update_pipe_fds(int *prev_pipe_read, int pipefd[2], int has_next)
{
	if (has_next)
	{
		close(pipefd[1]);
		*prev_pipe_read = pipefd[0];
	}
	else
		close(pipefd[0]);
}

int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}
