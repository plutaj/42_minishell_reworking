/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ignoring_pipes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:53:13 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/22 17:35:46 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	count_tokens_quote_aware(const char *s, char delim);
char	*alloc_token_quote_aware(const char *s, char delim, int *consumed_len);
char	**free_split(char **split, size_t count);
void	copy_token(char *dst, const char *src, int len);

char	**ft_split_quote_aware(const char *s, char delim)
{
	size_t	i = 0;
	size_t	len;
	char	**result;
	int		consumed;

	if (!s)
		return (NULL);
	len = count_tokens_quote_aware(s, delim);
	result = calloc(len + 1, sizeof(char *));
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
		while (*s == delim) // skip delim after token
			s++;
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	count_tokens_quote_aware(const char *s, char delim)
{
	int		i = 0;
	int		count = 0;
	char	quote = 0;

	while (s[i])
	{
		while (s[i] == delim)
			i++;
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
	int		i = 0;
	char	quote = 0;
	char	*token;

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

void	copy_token(char *dst, const char *src, int len)
{
	for (int i = 0; i < len; i++)
		dst[i] = src[i];
	dst[len] = '\0';
}

char	**free_split(char **split, size_t count)
{
	while (count--)
		free(split[count]);
	free(split);
	return (NULL);
}

// char		**free_split(char **split, size_t count);
// void		set_quote(char *quote, const char *s, int i);
// char		**ft_split_quote_aware(const char *s, char c);
// static int	count_tokens_quote_aware(const char *s, char c);
// static char	*alloc_token_quote_aware(const char *s, char c, int *consumed_len);

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
// 			return (free_split(result, i));
// 		s += consumed;
// 		i++;
// 	}
// 	result[i] = NULL;
// 	return (result);
// }

// static int	count_tokens_quote_aware(const char *s, char c)
// {
// 	int		i;
// 	int		count;
// 	char	quote;

// 	i = 0;
// 	count = 0;
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
// 			set_quote(&quote, s, i);
// 			if (!quote && (s[i] == '\'' || s[i] == '"'))
// 				quote = s[i];
// 			else if (!quote && s[i] == c)
// 				break ;
// 			i++;
// 		}
// 	}
// 	return (count);
// }

// void	set_quote(char *quote, const char *s, int i)
// {
// 	if (*quote && s[i] == *quote)
// 		*quote = 0;
// }

// static char	*alloc_token_quote_aware(const char *s, char c, int *consumed_len)
// {
// 	int		i;
// 	char	quote;
// 	char	*token;

// 	i = 0;
// 	quote = 0;
// 	while (s[i])
// 	{
// 		if (quote && s[i] == quote)
// 			quote = 0;
// 		else if (!quote && (s[i] == '\'' || s[i] == '"'))
// 			quote = s[i];
// 		else if (!quote && s[i] == c)
// 			break ;
// 		i++;
// 	}
// 	if (consumed_len)
// 		*consumed_len = i;
// 	token = malloc(i + 1);
// 	if (!token)
// 		return (NULL);
// 	copy_token(token, s, i);
// 	return (token);
// }

// char	**free_split(char **split, size_t count)
// {
// 	while (count--)
// 		free(split[count]);
// 	free(split);
// 	return (NULL);
// }

