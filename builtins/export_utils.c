/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:03:44 by jpluta            #+#    #+#             */
/*   Updated: 2025/08/06 14:26:40 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_var_value(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=' || str[i] == '\0')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (new_str = ft_strdup(""));
	i++;
	new_str = ft_substr(str, i, ft_strlen(str) - i);
	return (new_str);
}

void	print_exported_env(char **env)
{
	int		i;
	char	*eq_pos;

	i = 0;
	while (env[i])
	{
		eq_pos = ft_strchr(env[i], '=');
		if (eq_pos)
		{
			printf("declare -x %.*s=\"%s\"\n",
				(int)(eq_pos - env[i]), env[i], eq_pos + 1);
		}
		else
			printf("declare -x %s\n", env[i]);
		i++;
	}
}

void	cmd_export_set_var(t_data *data, char *arg)
{
	char	*var_name;
	char	*var_value;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		var_name = ft_substr(arg, 0, ft_index_of_pointer(arg, equal_sign));
	else
		var_name = ft_strdup(arg);
	var_value = extract_var_value(arg);
	if (update_env_var(data->env, var_name, var_value))
		g_last_exit_status = 0;
	else
		cmd_export_util(data, var_name);
	free(var_value);
}
