/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:29:40 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/08 17:37:33 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			**ft_split(char const *s, char c);
static int		alloc_mem_substrings(char const *s, char **str, char c);
static void		create_new_arr(char const *s, char **str, char c);
static size_t	get_len_of_substring(char const *s, size_t i, char c);
static size_t	get_num_of_strings(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	size_t	substr_num;
	char	**str;

	if (s == NULL)
		return (NULL);
	substr_num = get_num_of_strings(s, c);
	if (substr_num == 0)
		return (ft_calloc(1, sizeof(char *)));
	str = ft_calloc((substr_num + 1), sizeof(char *));
	if (str == NULL)
		return (NULL);
	if (alloc_mem_substrings(s, str, c))
		return (NULL);
	create_new_arr(s, str, c);
	return (str);
}

static int	alloc_mem_substrings(char const *s, char **str, char c)
{
	size_t	i;
	size_t	x;
	size_t	len;

	i = 0;
	x = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		len = get_len_of_substring(s, i, c);
		str[x] = ft_calloc(len + 1, sizeof(char));
		if (str[x] == NULL)
		{
			while (x > 0)
				free(str[--x]);
			free(str);
			return (1);
		}
		i += len;
		x++;
	}
	return (0);
}

static void	create_new_arr(char const *s, char **str, char c)
{
	size_t	i;
	size_t	y;
	size_t	x;
	size_t	substr_len;

	i = 0;
	x = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		substr_len = get_len_of_substring(s, i, c);
		y = 0;
		while (y < substr_len)
		{
			str[x][y] = s[i];
			i++;
			y++;
		}
		str[x][y] = '\0';
		x++;
	}
	str[x] = NULL;
}

static size_t	get_len_of_substring(char const *s, size_t i, char c)
{
	size_t	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static size_t	get_num_of_strings(char const *s, char c)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			n++;
			while (*s != c && *s)
				s++;
		}
	}
	return (n);
}
