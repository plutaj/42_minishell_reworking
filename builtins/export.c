/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:46:12 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/28 14:24:44 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cmd_export_util(t_data *data, char *var_name);

void	cmd_export(t_data *data)
{
    char	*var_name;
    char	*var_value;
    char	*equal_sign;

	if (!data->cmd_list->args[1])
	{
        print_exported_env(data->env);
		return;
	}
	if (export_syntax_invalid(data->cmd_list->args[1]))
    {
        printf_err_msg(data->cmd_list->args[1]);
        g_last_exit_status = 1;
        return;
    }
	equal_sign = ft_strchr(data->cmd_list->args[1], '=');
    if (equal_sign)
        var_name = ft_substr(data->cmd_list->args[1], 0,
            ft_index_of_pointer(data->cmd_list->args[1], equal_sign));
    else
        var_name = ft_strdup(data->cmd_list->args[1]);
    var_value = extract_var_value(data->cmd_list->args[1]);
	if (update_env_var(data->env, var_name, var_value))
        g_last_exit_status = 0;
    else
        cmd_export_util(data, var_name);
    free(var_value);
}

static void	cmd_export_util(t_data *data, char *var_name)
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
