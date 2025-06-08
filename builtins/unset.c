/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:33:37 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/08 13:39:36 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_unset(t_data *data)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;
	char	*key;

	if (!data || !data->env || !data->cmd_list
		|| !data->cmd_list->args || !data->cmd_list->args[1])
		return ;
	key = data->cmd_list->args[1];
	len = 0;
	while (data->env[len])
		len++;
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (!(ft_strncmp(data->env[i], key, ft_strlen(key)) == 0
				&& data->env[i][ft_strlen(key)] == '='))
		{
			new_env[j] = ft_strdup(data->env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_2d_array(data->env);
	data->env = new_env;
}


// void    cmd_unset(t_data *data)
// {
//     int i = 0;
//     int j = 0;
//     char **new_env;

//     // Count number of entries in env
//     while (data->env && data->env[i])
//         i++;

//     new_env = malloc(sizeof(char *) * i);
//     if (!new_env)
//         return ;

//     // Copy strings from old env to new env
//     while (j < i)
//     {
//         if (!ft_strnstr(data->env[j], data->cmd_list->args[1], ft_strlen(data->cmd_list->args[1])))
//             new_env[j] = ft_strdup(data->env[j]);
//         j++;
//     }
//     new_env[j] = NULL;  // Final NULL terminator
//     free_2d_array(data->env);
//     data->env = new_env;
// }