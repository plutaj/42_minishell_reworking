/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:55:21 by jpluta            #+#    #+#             */
/*   Updated: 2025/04/19 16:02:08 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		**ft_split(char const *s, char c);
static int	count_str(char const *s, char c);
static char	*alloc_substr_cpy(const char *s, char c);

char	**ft_split(char const *s, char c)
{
	size_t	len;
	size_t	i;
	char	**result;

	len = count_str(s, c);
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		while (s[0] == c)
			s++;
		result[i] = alloc_substr_cpy(s, c);
		if (!result[i])
		{
			free(result);
			return (NULL);
		}
		s = s + ft_strlen(result[i]);
	i++;
	}
	result[i] = 0;
	return (result);
}
static int	count_str(char const *s, char c)
{
	size_t	i;
	int	count;
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}
static char	*alloc_substr_cpy(const char *s, char c)
{
	size_t	i;
	char	*res;
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	res = malloc(i + 1);
	if (!res)
	{
		free(res);
		return (NULL);
	}
	ft_strlcpy(res, s, i + 1);
	return (res);
}