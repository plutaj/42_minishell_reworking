/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:46:12 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/08/06 14:34:19 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_export(t_data *data)
{
	char	*arg;

	arg = data->cmd_list->args[1];
	if (!arg)
	{
		print_exported_env(data->env);
		return ;
	}
	if (export_syntax_invalid(arg))
	{
		printf_err_msg(arg);
		g_last_exit_status = 1;
		return ;
	}
	cmd_export_set_var(data, arg);
}

void	cmd_export_util(t_data *data, char *var_name)
{
	create_env_var(data, data->cmd_list->args[1]);
	g_last_exit_status = 0;
	free(var_name);
}

void	printf_err_msg(char *str)
{
	write(STDERR_FILENO, "minishell: export: ", 19);
	if (str)
		write(STDERR_FILENO, str, ft_strlen(str));
	else
		(void)str;
	write(STDERR_FILENO, "not a valid identifier\n", 24);
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
