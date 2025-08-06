/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:46:18 by jpluta            #+#    #+#             */
/*   Updated: 2025/08/06 14:19:47 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_quotes(t_data *data)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	if (data == NULL || data->input == NULL)
		return (1);
	while (data->input[i])
	{
		if (data->input[i] == '\'' && !in_single && !in_double)
			in_single = 1;
		else if (data->input[i] == '\"' && !in_double && !in_single)
			in_double = 1;
		else if (data->input[i] == '\'' && in_single && !in_double)
			in_single = 0;
		else if (data->input[i] == '\"' && in_double && !in_single)
			in_double = 0;
		i++;
	}
	if (in_single || in_double)
		return (0);
	return (1);
}

static int	update_quote(char c, char *quote)
{
	if (c == '\'' || c == '"')
	{
		if (!(*quote))
		{
			*quote = c;
			return (1);
		}
		else if (*quote == c)
		{
			*quote = 0;
			return (1);
		}
	}
	return (0);
}

char	*remove_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	result = malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	quote = 0;
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (update_quote(str[i], &quote))
		{
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	is_valid_redirection(char **args)
{
	if (!args || !args[0] || !args[1])
		return (0);
	if (!ft_strcmp(args[0], "<") || !ft_strcmp(args[0], ">>")
		|| !ft_strcmp(args[0], ">") || !ft_strcmp(args[0], "<<"))
	{
		if (args[1][0] == '<' || args[1][0] == '>')
			return (0);
		return (1);
	}
	return (0);
}

void	remove_quotes_from_args(char **args)
{
	int		i;
	char	*cleaned;

	i = 0;
	while (args[i])
	{
		cleaned = remove_quotes(args[i]);
		if (cleaned)
		{
			free(args[i]);
			args[i] = cleaned;
		}
		i++;
	}
}
