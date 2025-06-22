/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:18:19 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/22 16:38:30 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_err_msg(char *str);
void	exit_err_msg2();

int builtin(t_command *cmd_list)
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

int builtin2(t_command *cmd_list)
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

void	exit_f(t_command *cmd_list)
{
	int		i = 0;
	char	*arg = cmd_list->args[1];

	if (cmd_list->args[2])
	{
		exit_err_msg2();
		free_2d_array(cmd_list->data->env);
    	set_data_to_default(cmd_list->data);
		return ;
	}
	else if (arg)
	{
		if ((arg[0] == '-' || arg[0] == '+') && arg[1] != '\0')
			i = 1;
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
			{
				exit_err_msg(arg);
				free_2d_array(cmd_list->data->env);
				set_data_to_default(cmd_list->data);
				exit(g_last_exit_status);
			}
			i++;
		}
		g_last_exit_status = atoi(arg);
	}
	else
		g_last_exit_status = 0;
	free_2d_array(cmd_list->data->env);
	set_data_to_default(cmd_list->data);
	exit(g_last_exit_status);
}

void	exit_err_msg(char *str)
{
	write(STDERR_FILENO, "minishell: exit: ", 17);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": numeric argument required", 27);
	g_last_exit_status = 2;
}

void	exit_err_msg2()
{
	write(STDERR_FILENO, "minishell$: exit: too many arguments", 36);
	g_last_exit_status = 1;
}