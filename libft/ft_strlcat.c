/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:40:46 by jpluta            #+#    #+#             */
/*   Updated: 2025/02/23 15:36:24 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// size_t  ft_strlcat(char *dest, const char *src, size_t size)
// {
//     size_t  i;
//     size_t  dest_len;
//     size_t  src_len;
//     char *s;    s = (char *)src;    i = 0;
//     dest_len = strlen(dest);
//     src_len = strlen(src);
//     if (size <= dest_len)
//         return (src_len + dest_len);
//     while (src[i] && (dest_len + i) < (size - 1))
//     {
//         dest[dest_len + i] = src[i];
//         i++;
//     }
//     dest[dest_len + i] = '\0';
//     return (dest_len + src_len);
// }

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	while (src[i] != '\0' && (dst_len + i) < (size - 1) && size != 0)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (size > dst_len)
		dst[dst_len + i] = '\0';
	if (size < (dst_len))
		return (size + src_len);
	return (src_len + dst_len);
}

// int main(void)
// {
// 	char	*dest_orig;
// 	char	*dest_ft;
// 	int		orig;
// 	int		ft;
// 	if (!(dest_orig = (char *)malloc(sizeof(*dest_orig) * 15)))
// 		return (0);
// 	memset(dest_orig, 0, 15);
// 	memset(dest_orig, 'r', 6);
// 	if (!(dest_ft = (char *)malloc(sizeof(*dest_ft) * 15)))
// 		return (0);
// 	memset(dest_ft, 0, 15);
// 	memset(dest_ft, 'r', 6);
// 	dest_orig[10] = 'a';
// 	dest_ft[10] = 'a';
// 	orig = 0;
// 	ft = 0;
// 	printf("orig: %i: %s %p\n", orig, dest_orig, dest_orig);
// 	printf("ft: %i: %s %p\n", ft, dest_ft, dest_ft);
// 	orig = strlcat(dest_orig, "lorem ipsum dolor sit amet", 5);
// 	ft = ft_strlcat(dest_ft, "lorem ipsum dolor sit amet", 5);
// 	printf("orig: %i: %s %p\n", orig, dest_orig, dest_orig);
// 	printf("ft: %i: %s %p\n", ft, dest_ft, dest_ft);
// 	return 0;
// }
