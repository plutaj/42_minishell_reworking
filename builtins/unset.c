/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:33:37 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/22 15:57:06 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	copy_env_excluding_key(char **src, char **dest, const char *key);

// void	cmd_unset(t_data *data)
// {
// 	int		len;
// 	char	**new_env;
// 	char	*key;

// 	if (data->cmd_list->args[2])
// 		return (unset_invalid_num_args());
// 	if (!data || !data->env || !data->cmd_list
// 		|| !data->cmd_list->args || !data->cmd_list->args[1])
// 		return ;
// 	key = data->cmd_list->args[1];
// 	len = count_rows_of_arr(data);
// 	new_env = malloc(sizeof(char *) * len);
// 	if (!new_env)
// 		return ;
// 	copy_env_excluding_key(data->env, new_env, key);
// 	free_2d_array(data->env);
// 	data->env = new_env;
// 	g_last_exit_status = 0;
// }

// static void	copy_env_excluding_key(char **src, char **dest, const char *key)
// {
// 	int 	i;
// 	int 	j;
// 	size_t 	key_len;

// 	i = 0;
// 	j = 0;
// 	key_len = ft_strlen(key);
// 	while (src[i])
// 	{
// 		if (!(ft_strncmp(src[i], key, key_len) == 0 && src[i][key_len] == '='))
// 		{
// 			dest[j] = ft_strdup(src[i]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	dest[j] = NULL;
// }

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
	// new_env = malloc(sizeof(char *) * (len + 1));
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

void	unset_invalid_num_args()
{
	// printf("minishell: unset: options aren't supported\n");
	g_last_exit_status = 0;
}

int	count_rows_of_arr(t_data *data)
{
	int len;

	len = 0;
	while (data->env[len])
		len++;
	return (len);
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