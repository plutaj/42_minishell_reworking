/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:24:59 by jpluta            #+#    #+#             */
/*   Updated: 2024/06/29 16:15:37 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
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

// int	main(void)
// {
// 	char	dest[50];

// 	strncpy(dest, "XXXXXXXXXXXXXXXXXX", sizeof(dest));
// 	ft_memcpy(dest, NULL, 15);
// 	printf("Test 1: %s\n", dest);
// 	return (0);
// }
