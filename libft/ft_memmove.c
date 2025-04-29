/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:30:42 by jpluta            #+#    #+#             */
/*   Updated: 2024/05/30 20:33:39 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*psrc;
	char		*pdest;

	psrc = (const char *)src;
	pdest = (char *)dest;
	i = 0;
	if (pdest < psrc)
	{
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	if (pdest > psrc)
	{
		i = n;
		while (i > 0)
		{
			pdest[i - 1] = psrc[i - 1];
			i--;
		}
	}
	return (dest);
}

// int main(void)
// {
// 	char src[50] = "abcdefgh";
// 	char dest[50] = "1234";
// 	ft_memmove(dest, src, 9);
// 	printf("%s", dest);

// 	return (0);
// }
