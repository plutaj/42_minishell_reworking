/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exbuil.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:07:29 by huahmad           #+#    #+#             */
/*   Updated: 2025/06/14 16:14:27 by jozefpluta       ###   ########.fr       */
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
		result = find_command_in_path(cmd_list->args[0]);
	if (result)
	{
		execute_command(result, cmd_list->args, data->env);
		free(result);
	}
	else
	{
		printf("minishell$: %s: command not found\n", cmd_list->args[0]);
		g_exit_status = 127;
	}
}
