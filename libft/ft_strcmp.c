/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:38:44 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/29 14:52:36 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	if (!str1 && !str2)
		return (0);
	if (!str1)
		return (-1);
	if (!str2)
		return (1);
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return ((unsigned char)*str1 - (unsigned char)*str2);
		str1++;
		str2++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}

// int ft_strcmp(const char *str1, const char *str2)
// {
//     // Compare each character one by one
//     while (*str1 != '\0' && *str2 != '\0')
//     {
//         if (*str1 != *str2)
//         {
//             return ((unsigned char)*str1 - (unsigned char)*str2);
//         }
//         str1++;
//         str2++;
//     }
//     // If both strings ended (i.e., null-terminator reached),
//     return ((unsigned char)*str1 - (unsigned char)*str2);
// }