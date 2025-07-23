/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:55:51 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/23 17:50:04 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variables(char **str, t_data *data)
{
	int	i;
	int	in_single_q;
	int	in_double_q;

	i = 0;
	in_single_q = 0;
	in_double_q = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\"' && !in_single_q)
			in_double_q = !in_double_q;
		else if ((*str)[i] == '\'' && !in_double_q)
			in_single_q = !in_single_q;
		if ((*str)[i] == '$' && !in_single_q)
		{
			handle_variable_expansion(str, data, &i);
			i = 0;
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
		if (str[i] == ' ' || str[i] == '$' || str[i] == '\'' || str[i] == '"'
			|| str[i] == '\0')
			break ;
		i++;
	}
	new_str = ft_substr(str, 0, i);
	return (new_str);
}
