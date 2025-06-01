/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:38:29 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/01 17:35:43 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_variables(t_command *new_cmd)
{
	int i = 0;

	while (new_cmd->args[i])
	{
		if (dollar_sign(new_cmd->args[i]))
			expand_variables(&(new_cmd->args[i]), new_cmd->data);
		i++;
	}
}

void	expand_variables(char **str, t_data *data)
{
	char	*ptr;
	char	*var;
	char	*new_str;
	char	*temp;
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			new_str = ft_substr(*str, 0, i);
			var = extract_var(&(*str)[i]);
			ptr = is_env_var(var, data->env);
			if (!ptr)
				ptr = "";
			temp = ft_strjoin(new_str, ptr);
			free(new_str);
			new_str = temp;
			temp = ft_strjoin(new_str, ptr);
			free(new_str);
			new_str = temp;
			free(*str);
			*str = new_str;
			i += ft_strlen(var);
			free(var);
			continue ;
		}
		i++;
	}
}

char	*extract_var(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '\'' || str[i] == '"' || str[i] == '\0')
			break;
		i++;
	}
	return ft_substr(str, 0, i);
}