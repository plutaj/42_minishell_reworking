/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:55:51 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/09 13:56:48 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variables(char **str, t_data *data)
{
	int		i;
	int		is_single_q;

	i = 0;
	is_single_q = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\'')
			is_single_q = !is_single_q;
		if ((*str)[i] == '$' && !is_single_q)
		{
			handle_variable_expansion(str, data, &i);
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
	if (str[i] == '?')
	{
		new_str = ft_substr(str, 0, 2);
		return (new_str);
	}
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '\'' || str[i] == '"' || str[i] == '\0')
			break ;
		i++;
	}
	new_str = ft_substr(str, 0, i);
	return (new_str);
}
