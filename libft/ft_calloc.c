/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:25:48 by jpluta            #+#    #+#             */
/*   Updated: 2024/06/08 17:38:28 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;
	size_t	total_size;

	total_size = nelem * elsize;
	if (nelem <= 0 || elsize <= 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	if (total_size / elsize != nelem)
		return (NULL);
	ptr = malloc(nelem * elsize);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}
/* alokuje unused space pre array 'nelem'entov kde velkost
jedneho je 'elsize' */
