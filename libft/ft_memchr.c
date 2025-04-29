/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:34:34 by jpluta            #+#    #+#             */
/*   Updated: 2024/05/30 20:33:30 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ps;

	i = 0;
	ps = (const unsigned char *)s;
	while (i < n)
	{
		if (ps[i] == (unsigned char)c)
			return ((void *)(ps + i));
		i++;
	}
	return (NULL);
}
