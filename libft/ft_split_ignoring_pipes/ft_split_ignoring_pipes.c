/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ignoring_pipes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:53:13 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/29 18:04:08 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		**ft_split_quote_aware(const char *s, char c);
static int	count_tokens_quote_aware(const char *s, char c);
static char	*alloc_token_quote_aware(const char *s, char c, int *consumed_len);

char	**ft_split_quote_aware(const char *s, char c)
{
	size_t	i = 0;
	size_t	len = count_tokens_quote_aware(s, c);
	char	**result = ft_calloc(len + 1, sizeof(char *));
	int		consumed;

	if (!result)
		return (NULL);

	while (i < len)
	{
		while (*s == c)
			s++;
		result[i] = alloc_token_quote_aware(s, c, &consumed);
		if (!result[i])
		{
			// Free previously allocated tokens
			while (i--)
				free(result[i]);
			free(result);
			return (NULL);
		}
		s += consumed;
		i++;
	}
	result[i] = NULL;
	return (result);
}

static int	count_tokens_quote_aware(const char *s, char c)
{
	int		count = 0;
	int		i = 0;
	char	quote = 0;

	while (s[i])
	{
		// Skip delimiters
		while (s[i] == c)
			i++;

		if (!s[i])
			break;

		count++;

		// Advance until delimiter outside quotes or end
		while (s[i])
		{
			if (quote)
			{
				if (s[i] == quote)
					quote = 0;
			}
			else
			{
				if (s[i] == '\'' || s[i] == '"')
					quote = s[i];
				else if (s[i] == c)
					break;
			}
			i++;
		}
	}

	return (count);
}

static char	*alloc_token_quote_aware(const char *s, char c, int *consumed_len)
{
	int		i = 0;
	char	quote = 0;

	while (s[i])
	{
		if (quote)
		{
			if (s[i] == quote)
				quote = 0;
		}
		else
		{
			if (s[i] == '\'' || s[i] == '"')
				quote = s[i];
			else if (s[i] == c)
				break;
		}
		i++;
	}

	if (consumed_len)
		*consumed_len = i;

	// Allocate and copy the token
	char *token = malloc(i + 1);
	if (!token)
		return (NULL);
	for (int j = 0; j < i; j++)
		token[j] = s[j];
	token[i] = '\0';

	return token;
}
