/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:58 by jpluta            #+#    #+#             */
/*   Updated: 2025/02/23 15:37:19 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*do_conversion(int n, int original_n, int digits, char *str);

char	*ft_itoa(int n)
{
	int		digits;
	int		original_n;
	char	*str;

	str = NULL;
	digits = 0;
	original_n = n;
	if (n == 0)
	{
		str = malloc(2);
		if (str == NULL)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (do_conversion(n, original_n, digits, str));
}

static char	*do_conversion(int n, int original_n, int digits, char *str)
{
	while (original_n != 0)
	{
		original_n = original_n / 10;
		digits++;
	}
	if (n < 0)
		digits++;
	str = (char *)malloc(digits + 1);
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = n * (-1);
	}
	str[digits] = '\0';
	digits--;
	while (n != 0)
	{
		str[digits] = (n % 10) + '0';
		n = n / 10;
		digits--;
	}
	return (str);
}
