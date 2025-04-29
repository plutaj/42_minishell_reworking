/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:39:45 by jpluta            #+#    #+#             */
/*   Updated: 2024/06/01 12:58:16 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
// int		main()
// {
// 	char	*dst;
// 	int		*src;
// 	if (!(dst = (char *)malloc(sizeof(*dst) * 15)))
// 		return (0);
// 	memset(dst, 0, 15);
// 	memset(dst, 'r', 6);
// 	printf("%zu\n", ft_strlcpy(dst, "lorem ipsum dolor sit amet", 15));
// 	printf("%s\n", dst);
// 	free(dst);

// 	return (0);
// }

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
