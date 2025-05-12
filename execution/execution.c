/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:46:03 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/12 18:53:06 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execution(t_data *data)
{
    // One command case (0 pipes)
    if (!data->cmd_list->next)
    {
        if (is_builtin(data->cmd_list))
        {
            printf("is builtin\n");
        }
        else if (is_external(data->cmd_list))
        {
            
        }
        // else
            //case of invalid command  
    }
    
}

int is_builtin(t_command *cmd_list)
{
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
    return (0);
}

int is_external(t_command *cmd_list)
{
    if (ft_strchr(cmd_list->args[0], '/'))
    {
        if (access(cmd_list->args, X_OK) == 0)
            printf("found in path /"); // fork and exec
    } 
    else
    {
        // search cmd in each $PATH entry:
        //     check access(path + "/" + cmd, X_OK);
    }
    if found:
        execve(...)
    else:
        print error
}