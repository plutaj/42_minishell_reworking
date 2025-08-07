/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:55:51 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/07 18:19:19 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_dollar_sign(char **str, t_data *data, int *i)
{
	if ((*str)[*i + 1] == '?')
	{
		*str = ft_strjoin_f(*str, ft_itoa(g_last_exit_status), *i);
		*i = 0;
	}
	else if ((*str)[*i + 1] == '\0' || !ft_isalnum((*str)[*i + 1]))
		*i = 0;
	else if ((*str)[*i + 1] == '\'' || (*str)[*i + 1] == '"')
	{
		*str = ft_strjoin_f(*str, ft_substr(*str, *i + 1, 1), *i);
		*i = 0;
	}
	else
	{
		handle_variable_expansion(str, data, i); //there is a value that is being initialized inside this function that should be initialized before, that is probably why it is causing the leak only once
		*i = 0;
	}
}

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
			handle_dollar_sign(str, data, &i);
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

char	*ft_strjoin_f(char *s1, char *s2, int j)
{
	char	*joined;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < (size_t)j && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	k = 0;
	while (s2[k])
		joined[i++] = s2[k++];
	j += 2;
	while (i < (ft_strlen(s1) + ft_strlen(s2) + 1) - 1 && s1[j])
	{
		joined[i++] = s1[j++];
	}
	joined[i] = 0;
	return (free(s1), free(s2), joined);
}
