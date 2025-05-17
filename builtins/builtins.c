/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:18:19 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/17 15:20:53 by jpluta           ###   ########.fr       */
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
        return (1);
    return (0);
}