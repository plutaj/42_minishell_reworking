/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:29:32 by jpluta            #+#    #+#             */
/*   Updated: 2024/06/01 14:39:35 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

// int main(void)
// {
// 	printf("%s", ft_strnstr("lorem ipsum dolor sit amet", "ipsum", 15));
// 	return (0);
// }

char	*ft_strnstr(const char *big, const char *little, size_t len)
		// lokalizuje prvy vyskyt 'little' stringu v 'big'
{
	size_t	bi;
	size_t	li;
	size_t	start;

	bi = 0;
	li = 0;
	if (little[li] == '\0')
		return ((char *)big);
	while (big[bi] != '\0' && bi < len)
	{
		start = bi;
		while (big[bi] == little[li] && bi < len && little[li] != '\0'
			&& big[bi] != '\0')
		{
			li++;
			bi++;
		}
		if (little[li] == '\0')
			return ((char *)&big[start]);
		bi = start;
		li = 0;
		bi++;
	}
	return (NULL);
}
