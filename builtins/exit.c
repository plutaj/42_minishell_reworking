/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:02:27 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/22 17:02:54 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_err_msg(char *str, t_command *cmd_list);
static void	exit_err_msg2(t_command *cmd_list);
static void ft_clean_n_exit(t_command *cmd_list);

void	exit_f(t_command *cmd_list)
{
	int		i;
	char	*arg;

	i = 0;
	arg = cmd_list->args[1];
	if (cmd_list->args[2])
	{
		exit_err_msg2(cmd_list);
		return ;
	}
	else if (arg)
	{
		if ((arg[0] == '-' || arg[0] == '+') && arg[1] != '\0')
			i = 1;
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
				exit_err_msg(arg, cmd_list);
			i++;
		}
		g_last_exit_status = ft_atoi(arg);
	}
	else
		g_last_exit_status = 0;
	ft_clean_n_exit(cmd_list);
}

static void	exit_err_msg(char *str, t_command *cmd_list)
{
	write(STDERR_FILENO, "minishell: exit: ", 17);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": numeric argument required", 27);
	free_2d_array(cmd_list->data->env);
	set_data_to_default(cmd_list->data);
	g_last_exit_status = 2;
	exit(g_last_exit_status);
}

static void	exit_err_msg2(t_command *cmd_list)
{
	write(STDERR_FILENO, "minishell$: exit: too many arguments", 36);
	free_2d_array(cmd_list->data->env);
	set_data_to_default(cmd_list->data);
	g_last_exit_status = 1;
}

static void ft_clean_n_exit(t_command *cmd_list)
{
	free_2d_array(cmd_list->data->env);
	set_data_to_default(cmd_list->data);
	exit(g_last_exit_status);
}
