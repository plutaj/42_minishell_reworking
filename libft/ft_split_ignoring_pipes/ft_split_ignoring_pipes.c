/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ignoring_pipes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:53:13 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/08 18:01:53 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		**free_split(char **split, size_t count);
void		set_quote(char *quote, const char *s, int i);
char		**ft_split_quote_aware(const char *s, char c);
static int	count_tokens_quote_aware(const char *s, char c);
static char	*alloc_token_quote_aware(const char *s, char c, int *consumed_len);

char	**ft_split_quote_aware(const char *s, char c)
{
	size_t	i;
	size_t	len;
	char	**result;
	int		consumed;

	i = 0;
	len = count_tokens_quote_aware(s, c);
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (i < len)
	{
		while (*s == c)
			s++;
		result[i] = alloc_token_quote_aware(s, c, &consumed);
		if (!result[i])
			return (free_split(result, i));
		s += consumed;
		i++;
	}
	result[i] = NULL;
	return (result);
}

static int	count_tokens_quote_aware(const char *s, char c)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i])
		{
			set_quote(&quote, s, i);
			if (!quote && (s[i] == '\'' || s[i] == '"'))
				quote = s[i];
			else if (!quote && s[i] == c)
				break ;
			i++;
		}
	}
	return (count);
}

void	set_quote(char *quote, const char *s, int i)
{
	if (*quote && s[i] == *quote)
		*quote = 0;
}

static char	*alloc_token_quote_aware(const char *s, char c, int *consumed_len)
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
		else if (!quote && (s[i] == '\'' || s[i] == '"'))
			quote = s[i];
		else if (!quote && s[i] == c)
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

// char		**ft_split_quote_aware(const char *s, char c);
// static int	count_tokens_quote_aware(const char *s, char c);
// static char	*alloc_token_quote_aware(const char *s,
// char c, int *consumed_len);

// char	**ft_split_quote_aware(const char *s, char c)
// {
// 	size_t	i;
// 	size_t	len;
// 	char	**result;
// 	int		consumed;

// 	i = 0;
// 	len = count_tokens_quote_aware(s, c);
// 	result = ft_calloc(len + 1, sizeof(char *));
// 	if (!result)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		while (*s == c)
// 			s++;
// 		result[i] = alloc_token_quote_aware(s, c, &consumed);
// 		if (!result[i])
// 		{
// 			while (i--)
// 				free(result[i]);
// 			free(result);
// 			return (NULL);
// 		}
// 		s += consumed;
// 		i++;
// 	}
// 	result[i] = NULL;
// 	return (result);
// }

// static int	count_tokens_quote_aware(const char *s, char c)
// {
// 	int		count;
// 	int		i;
// 	char	quote;

// 	count = 0;
// 	i = 0;
// 	quote = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (!s[i])
// 			break ;
// 		count++;
// 		while (s[i])
// 		{
// 			if (quote)
// 			{
// 				if (s[i] == quote)
// 					quote = 0;
// 			}
// 			else
// 			{
// 				if (s[i] == '\'' || s[i] == '"')
// 					quote = s[i];
// 				else if (s[i] == c)
// 					break ;
// 			}
// 			i++;
// 		}
// 	}
// 	return (count);
// }

// static char	*alloc_token_quote_aware(const char *s,
// char c, int *consumed_len)
// {
// 	int		i;
// 	char	quote;
// 	char	*token;

// 	i = 0;
// 	quote = 0;
// 	while (s[i])
// 	{
// 		if (quote)
// 		{
// 			if (s[i] == quote)
// 				quote = 0;
// 		}
// 		else
// 		{
// 			if (s[i] == '\'' || s[i] == '"')
// 				quote = s[i];
// 			else if (s[i] == c)
// 				break ;
// 		}
// 		i++;
// 	}
// 	if (consumed_len)
// 		*consumed_len = i;
// 	token = malloc(i + 1);
// 	if (!token)
// 		return (NULL);
// 	for (int j = 0; j < i; j++)
// 		token[j] = s[j];
// 	token[i] = '\0';
// 	return (token);
// }
