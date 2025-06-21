/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:46:12 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/21 13:25:48 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    cmd_export(t_data *data)
{
    char    *var_name;
    char    *var_value;
	char	*equal_sign;

    equal_sign = ft_strchr(data->cmd_list->args[1], '=');
	if (equal_sign)
		var_name = ft_substr(data->cmd_list->args[1], 0,
				ft_index_of_pointer(data->cmd_list->args[1], equal_sign));
	else
		var_name = ft_strdup(data->cmd_list->args[1]);
    var_value = extract_var_value(data->cmd_list->args[1]);
	if (!var_name) // case export without param (should print all exported env vars)
	{
		print_exported_env(data->env);
		g_last_exit_status = 0;
	}
    else if (update_env_var(data->env, var_name, var_value)) // case that is already exist in env var
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
            printf("minishell: export: '%s': not a valid identifier\n", data->cmd_list->args[1]);
			g_last_exit_status = 1;
		}
    }
    free(var_value);
}

void    create_env_var(t_data *data, char *var)
{
    int i = 0;
    int j = 0;
    char **new_env;

    // Count number of entries in env
    while (data->env && data->env[i])
        i++;

    // Allocate new array (+1 for new var, +1 for NULL terminator)
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return ;

    // Copy strings from old env to new env
    while (j < i)
    {
        new_env[j] = ft_strdup(data->env[j]);
        j++;
    }

    new_env[j] = ft_strdup(var);       // Slot for the new variable
    new_env[j + 1] = NULL;   // Final NULL terminator
    
    free_2d_array(data->env);
    data->env = new_env;
}

int is_valid_syntax(char *str)
{
    int i;
    
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
			break;
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
    int i = 0;
    char *eq_pos;

    while (env[i])
    {
        eq_pos = ft_strchr(env[i], '=');
        if (eq_pos)
        {
            // Print as: declare -x VAR="value"
            printf("declare -x %.*s=\"%s\"\n",
                   (int)(eq_pos - env[i]),  // length of variable name
                   env[i],                  // start of string
                   eq_pos + 1);             // value part (after '=')
        }
        else
        {
            // Variable without '=' (no value)
            printf("declare -x %s\n", env[i]);
        }
        i++;
    }
}