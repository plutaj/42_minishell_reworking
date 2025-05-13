/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:34:46 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/13 16:34:57 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcat(char *dest, const char *src)
{
    // Find the end of the destination string
    char *dest_ptr = dest;
    while (*dest_ptr)  // Iterate until we find the null-terminator of dest
        dest_ptr++;

    // Append the source string to the destination string
    while (*src) {
        *dest_ptr = *src;  // Copy the current character from src to dest
        dest_ptr++;
        src++;  // Move to the next character in src
    }

    // Null-terminate the result string
    *dest_ptr = '\0';

    return dest;  // Return the concatenated string
}