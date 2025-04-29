/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:33:55 by jpluta            #+#    #+#             */
/*   Updated: 2024/07/28 14:50:40 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	is_char(char a, int *len)
{
	*len += write(1, &a, 1);
}

void	is_pointer(size_t pointer, int *len)
{
	char	string[25];
	char	*hexa;
	size_t	i;

	hexa = "0123456789abcdef";
	i = 0;
	if (pointer == 0)
	{
		*len += write(1, "(nil)", 5);
		return ;
	}
	*len += write(1, "0x", 2);
	while (pointer != 0)
	{
		string[i] = hexa[pointer % 16];
		pointer = pointer / 16;
		i++;
	}
	while (i--)
	{
		*len += write(1, &string[i], 1);
	}
}

void	is_string(char *s, int *len)
{
	if (s == NULL)
	{
		*len += write(1, "(null)", 6);
	}
	else
	{
		while (*s)
		{
			*len += write(1, s, 1);
			s++;
		}
	}
}
