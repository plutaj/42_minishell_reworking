/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:18:19 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/17 20:09:09 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin(t_command *cmd_list)
{
    if (ft_strcmp("echo", cmd_list->args[0]) == 0)
	{
		cmd_echo(cmd_list);
		return (1);
	}
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
    {
        free_2d_array(cmd_list->data->env);
        set_data_to_default(cmd_list->data);
        exit(0);
    }
    return (0);
}