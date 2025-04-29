/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:03:29 by jpluta            #+#    #+#             */
/*   Updated: 2024/07/28 14:51:35 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	form_spec_check(const char *string, va_list args, int *len)
{
	char	str[15];

	if (*string == '%')
		*len += write(1, "%", 1);
	else if (*string == 'c')
		is_char(va_arg(args, int), len);
	else if (*string == 's')
		is_string(va_arg(args, char *), len);
	else if (*string == 'p')
		is_pointer(va_arg(args, size_t), len);
	else if (*string == 'i' || *string == 'd')
		is_int(va_arg(args, int), str, len);
	else if (*string == 'u')
		is_uint(va_arg(args, unsigned int), str, len);
	else if (*string == 'x')
		is_shexa(va_arg(args, unsigned int), len);
	else if (*string == 'X')
		is_bhexa(va_arg(args, unsigned int), len);
}

int	ft_printf(const char *string, ...)
{
	int		length;
	size_t	i;
	va_list	args;

	length = 0;
	i = 0;
	va_start(args, string);
	while (string[i])
	{
		if (string[i] == '%')
		{
			i++;
			form_spec_check(&string[i], args, &length);
			i++;
		}
		else
		{
			length++;
			write(1, &string[i], 1);
			i++;
		}
	}
	va_end(args);
	return (length);
}

// int	main(void)
// {
// 	int	i;

// 	i = 0;
// // 	// i = ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%
// // %X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%%%%c%%%s%%%d%%%i%%%u%%%x%%%X%
// // %%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,
// // -42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
// // 	i = ft_printf(" %% ");
// // 	ft_printf("%d", i);
// 	// i = printf("ORIGINAL : NULL %s NULL\n", NULL);
// 	// printf("%d\n", i);
// 	i = ft_printf("FT : NULL %s NULL \n", NULL);
// 	ft_printf("%d\n", i);

// 	return (0);
// }
