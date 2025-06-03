/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:38:29 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/03 20:04:29 by jozefpluta       ###   ########.fr       */
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
	char	*ptr_to_env;
	char	*var;
	char	*start;
	char	*temp;
	int		i;
	int		is_single_q;

	i = 0;
	is_single_q = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\'')
		{
			if (!is_single_q)
				is_single_q = 1;
			else
				is_single_q = 0;
		}
		// if ((*str)[i] == '$') // "test $HOME test2"
		if ((*str)[i] == '$' && !is_single_q) // "test $HOME test2"
		{
			start = ft_substr(*str, 0, i);
			var = extract_var(&(*str)[i]);
			ptr_to_env = is_env_var(var, data->env); // "/home/jozefpluta"
			if (!ptr_to_env)
				ptr_to_env = "";
			temp = ft_strjoin(start, ptr_to_env); // "test /home/jozefpluta"
			free(start);
			if ((*str)[i + (ft_strlen(var))] != '\0')
				start = ft_strdup(&(*str)[i + ft_strlen(var)]);
			else
				start = ft_strdup("");
			free(*str);
			*str = ft_strjoin(temp, start);
			i = 0;
			free(var);
			if (start)
				free(start);
			free(temp);
			continue ;
		}
		i++;
	}
}

char	*extract_var(char *str)
{
	int		i;
	char	*new_str;

	i = 1;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '\'' || str[i] == '"' || str[i] == '\0')
			break;
		i++;
	}
	new_str = ft_substr(str, 0, i);
	printf("from extract var |%s|", new_str);
	// return ft_substr(str, 0, i);
	return (new_str);
}