/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:33:37 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/28 12:17:14 by jpluta           ###   ########.fr       */
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

	if (data->cmd_list->args[2])
		return (unset_invalid_num_args());
	if (!data || !data->env || !data->cmd_list
		|| !data->cmd_list->args || !data->cmd_list->args[1])
		return ;
	key = data->cmd_list->args[1];
	len = count_rows_of_arr(data);
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (!(ft_strncmp(data->env[i], key, ft_strlen(key)) == 0
				&& (data->env[i][ft_strlen(key)] == '='
				|| data->env[i][ft_strlen(key)] == '\0')))
		{
			new_env[j] = ft_strdup(data->env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_2d_array(data->env);
	g_last_exit_status = 0;
	data->env = new_env;
}

void	unset_invalid_num_args(void)
{
	g_last_exit_status = 0;
}

int	count_rows_of_arr(t_data *data)
{
	int	len;

	len = 0;
	while (data->env[len])
		len++;
	return (len);
}
