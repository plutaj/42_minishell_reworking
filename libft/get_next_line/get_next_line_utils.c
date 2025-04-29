/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:23:43 by jpluta            #+#    #+#             */
/*   Updated: 2025/03/17 17:26:06 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup2(char *s1)
{
	char			*dest;
	unsigned int	i;
	size_t			s1_len;

	s1_len = 0;
	if (!s1 || s1 == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		s1_len++;
		s1++;
	}
	s1 = s1 - s1_len;
	dest = (char *)malloc(s1_len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

void	*ft_memcpy2(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*srce;

	dest = (unsigned char *)dst;
	srce = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = srce[i];
		i++;
	}
	return ((void *)dest);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;

	len1 = 0;
	len2 = 0;
	if (s1)
	{
		while (s1[len1] != '\0')
			len1++;
	}
	if (s1)
	{
		while (s2[len2] != '\0')
			len2++;
	}
	joined = (char *)malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	if (s1)
		ft_memcpy2(joined, s1, len1);
	if (s2)
		ft_memcpy2(joined + len1, s2, len2 + 1);
	return (joined);
}

char	*ft_strchr2(const char *s, int c)
{
	size_t	i;
	char	a;

	i = 0;
	a = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == a)
			return ((char *)&s[i]);
		i++;
	}
	if (a == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*get_remainder(char *buffer)
{
	char	*newline_pos;
	char	*rest;

	newline_pos = ft_strchr2(buffer, '\n');
	rest = NULL;
	if (newline_pos)
	{
		rest = ft_strdup2(newline_pos + 1);
		return (rest);
	}
	return (NULL);
}
