/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:42:01 by jpluta            #+#    #+#             */
/*   Updated: 2024/07/02 16:56:31 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// int main(void)
// {
// 	// ft_strchr("tripouille", 't');
// 	printf("%s\n", ft_strchr("teste", 'eman '));
// 	return (0);
// }

char	*ft_strchr(const char *s, int c)
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
	return (0);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	int		i;
// 	char	cc;

// 	i = 0;
// 	cc = (char)c;
// 	while (s[i])
// 	{
// 		if (s[i] == cc)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	if (cc == '\0')
// 		return ((char *)&s[i]);
// 	return (NULL);
// }
