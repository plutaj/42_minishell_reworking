/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:26:45 by jpluta            #+#    #+#             */
/*   Updated: 2024/05/30 20:34:04 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
		// duplikuje string a alokuje miesto v pamati pomocou  malloc
{
	size_t	slen;
	char	*newstr;

	slen = ft_strlen(s) + 1;
	if (s == NULL)
		return (NULL);
	newstr = malloc(slen);
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s, slen);
	return (newstr);
}
