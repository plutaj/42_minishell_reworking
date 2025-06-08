/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:46:12 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/08 12:22:16 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    cmd_export(t_data *data)
{
    char    *var_name;
    char    *var_value;

    var_name = data->cmd_list->args[1];
    var_value = extract_var_value(data->cmd_list->args[1]);
    if (update_env_var(data->env, var_name, var_value)) // case that is already exist in env var
        return ;
    else
    {
        if (is_valid_syntax(data->cmd_list->args[1]))
            create_env_var(data, data->cmd_list->args[1]);
        else
            printf("export: '%s': not a valid identifier", data->cmd_list->args[1]);
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