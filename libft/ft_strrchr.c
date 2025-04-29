/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:10:41 by jpluta            #+#    #+#             */
/*   Updated: 2024/05/30 20:34:35 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
// vrati pointer posledneho vyskytu 'c' charakteru
{
	size_t				i;
	const unsigned char	*ps;
	char				*result;
	unsigned char		nc;

	i = 0;
	ps = (const unsigned char *)s;
	result = NULL;
	nc = (unsigned char)c;
	while (ps[i] != '\0')
	{
		if (ps[i] == nc)
		{
			result = (char *)&ps[i];
		}
		i++;
	}
	if (nc == '\0')
		return ((char *)&ps[i]);
	return ((char *)result);
}
