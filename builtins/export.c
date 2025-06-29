/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:46:12 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/29 14:04:28 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printf_err_msg(char *str);

void	cmd_export(t_data *data)
{
	char	*var_name;
	char	*var_value;
	char	*equal_sign;

	equal_sign = ft_strchr(data->cmd_list->args[1], '=');
	if (equal_sign)
		var_name = ft_substr(data->cmd_list->args[1], 0,
				ft_index_of_pointer(data->cmd_list->args[1], equal_sign));
	else
		var_name = ft_strdup(data->cmd_list->args[1]);
	var_value = extract_var_value(data->cmd_list->args[1]);
	if (!var_name)
	{
		print_exported_env(data->env);
		g_last_exit_status = 0;
	}
	else if (update_env_var(data->env, var_name, var_value))
		g_last_exit_status = 0;
	else
	{
		if (is_valid_syntax(data->cmd_list->args[1]))
		{
			create_env_var(data, data->cmd_list->args[1]);
			g_last_exit_status = 0;
		}
		else
		{
			printf_err_msg(data->cmd_list->args[1]);
			g_last_exit_status = 1;
		}
	}
	free(var_value);
}

void	printf_err_msg(char *str)
{
	write(STDERR_FILENO, "minishell: export: ", 19);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": not a valid identifier\n", 25);
}

void	create_env_var(t_data *data, char *var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (data->env && data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	while (j < i)
	{
		new_env[j] = ft_strdup(data->env[j]);
		j++;
	}
	new_env[j] = ft_strdup(var);
	new_env[j + 1] = NULL;
	free_2d_array(data->env);
	data->env = new_env;
}

int	is_valid_syntax(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
