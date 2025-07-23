/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ignoring_pipes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:53:13 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/23 17:03:20 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		count_tokens_quote_aware(const char *s, char delim);
char	*alloc_token_quote_aware(const char *s, char delim, int *consumed_len);
char	**free_split(char **split, size_t count);
void	copy_token(char *dst, const char *src, int len);

char	**ft_split_quote_aware(const char *s, char delim)
{
	size_t	i;
	size_t	len;
	char	**result;
	int		consumed;

	i = 0;
	len = count_tokens_quote_aware(s, delim);
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (i < len)
	{
		while (*s == delim)
			s++;
		result[i] = alloc_token_quote_aware(s, delim, &consumed);
		if (!result[i])
			return (free_split(result, i));
		s += consumed;
		while (*s == delim)
			s++;
		i++;
	}
	result[i] = NULL;
	return (result);
}

void	div_func(const char *s, int *i, char delim)
{
	while (s[*i] == delim)
		(*i)++;
}

int	count_tokens_quote_aware(const char *s, char delim)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{
		div_func(s, &i, delim);
		if (!s[i])
			break ;
		count++;
		while (s[i])
		{
			if (quote && s[i] == quote)
				quote = 0;
			else if (!quote && (s[i] == '"' || s[i] == '\''))
				quote = s[i];
			else if (!quote && s[i] == delim)
				break ;
			i++;
		}
	}
	return (count);
}

char	*alloc_token_quote_aware(const char *s, char delim, int *consumed_len)
{
	int		i;
	char	quote;
	char	*token;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (quote && s[i] == quote)
			quote = 0;
		else if (!quote && (s[i] == '"' || s[i] == '\''))
			quote = s[i];
		else if (!quote && s[i] == delim)
			break ;
		i++;
	}
	if (consumed_len)
		*consumed_len = i;
	token = malloc(i + 1);
	if (!token)
		return (NULL);
	copy_token(token, s, i);
	return (token);
}

char	**free_split(char **split, size_t count)
{
	while (count--)
		free(split[count]);
	free(split);
	return (NULL);
}
