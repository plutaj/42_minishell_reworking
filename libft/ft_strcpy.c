/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:38:00 by jpluta            #+#    #+#             */
/*   Updated: 2025/04/26 12:40:19 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
    char	*ptr;
	
	ptr = dest;
    while (*src)
        *ptr++ = *src++;
    *ptr = '\0';
    return (dest);
}