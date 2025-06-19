/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_of_pointer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:38:01 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/19 16:14:04 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_index_of_pointer(const char *str, const char *ptr)
{
	if (!str || !ptr)
		return (0);
	return (size_t)(ptr - str);
}
