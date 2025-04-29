/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:28:32 by jpluta            #+#    #+#             */
/*   Updated: 2024/05/30 20:33:28 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t		i;
	char		*pdest;
	const char	*psrc;

	i = 0;
	pdest = (char *)dest;
	psrc = src;
	while (n != 0)
	{
		pdest[i] = psrc[i];
		if (psrc[i] == c)
			return ((void *)pdest + i + 1);
		i++;
		n--;
	}
	return (NULL);
}
