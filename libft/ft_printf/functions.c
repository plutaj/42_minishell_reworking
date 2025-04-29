/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:56:56 by jpluta            #+#    #+#             */
/*   Updated: 2024/07/28 13:34:50 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	do_conversion(unsigned int num, unsigned int original_n, int digits,
		char *str)
{
	while (original_n != 0)
	{
		original_n = original_n / 10;
		digits++;
	}
	str[digits--] = '\0';
	while (num != 0)
	{
		str[digits] = (num % 10) + '0';
		num = num / 10;
		digits--;
	}
}

void	is_int(int num, char *str, int *len)
{
	int	original_n;
	int	digits;

	digits = 0;
	if (num == 0)
	{
		*len += write(1, "0", 1);
		return ;
	}
	if (num == -2147483648)
	{
		*len += write(1, "-2147483648", 11);
		return ;
	}
	if (num < 0)
	{
		digits++;
		str[0] = '-';
		num = -num;
	}
	original_n = num;
	do_conversion(num, original_n, digits, str);
	is_string(str, len);
}

void	is_uint(unsigned int n, char *str, int *len)
{
	unsigned int	original_n;
	int				digits;

	original_n = n;
	digits = 0;
	if (n == 0)
	{
		*len += write(1, "0", 1);
		return ;
	}
	do_conversion(n, original_n, digits, str);
	is_string(str, len);
}

void	is_shexa(unsigned int hexn, int *len)
{
	char	string[25];
	char	*hexa;
	size_t	i;

	hexa = "0123456789abcdef";
	i = 0;
	if (hexn == 0)
	{
		*len += write(1, "0", 1);
		return ;
	}
	while (hexn != 0)
	{
		string[i] = hexa[hexn % 16];
		hexn = hexn / 16;
		i++;
	}
	while (i--)
	{
		*len += write(1, &string[i], 1);
	}
}

void	is_bhexa(unsigned int hexn, int *len)
{
	char	string[25];
	char	*hexa;
	size_t	i;

	hexa = "0123456789ABCDEF";
	i = 0;
	if (hexn == 0)
	{
		*len += write(1, "0", 1);
		return ;
	}
	while (hexn != 0)
	{
		string[i] = hexa[hexn % 16];
		hexn = hexn / 16;
		i++;
	}
	while (i--)
	{
		*len += write(1, &string[i], 1);
	}
}
