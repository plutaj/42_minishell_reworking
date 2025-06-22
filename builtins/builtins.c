/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:18:19 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/22 17:09:29 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin(t_command *cmd_list)
{
	if (ft_strcmp("echo", cmd_list->args[0]) == 0)
	{
		cmd_echo(cmd_list);
		return (1);
	}
	else if (ft_strcmp("cd", cmd_list->args[0]) == 0)
	{
		cmd_cd(cmd_list->data);
		return (1);
	}
	else if (ft_strcmp("pwd", cmd_list->args[0]) == 0)
	{
		cmd_pwd(cmd_list->data);
		return (1);
	}
	else if (ft_strcmp("export", cmd_list->args[0]) == 0)
	{
		cmd_export(cmd_list->data);
		return (1);
	}
	if (builtin2(cmd_list) == 0)
		return (1);
	else
		return (0);
}

int	builtin2(t_command *cmd_list)
{
	if (ft_strcmp("unset", cmd_list->args[0]) == 0)
	{
		cmd_unset(cmd_list->data);
		return (1);
	}
	else if (ft_strcmp("env", cmd_list->args[0]) == 0)
	{
		if (cmd_list->args[1] != NULL)
		{
			printf("minishell: env: Arguments and options aren't supported\n");
			g_last_exit_status = 127;
			return (1);
		}
		else
		{
			print_env(cmd_list->data->env);
			return (1);
		}
	}
	else if (ft_strcmp("exit", cmd_list->args[0]) == 0)
		exit_f(cmd_list);
	return (0);
}
