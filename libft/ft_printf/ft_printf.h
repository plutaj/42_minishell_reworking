/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:18:04 by jpluta            #+#    #+#             */
/*   Updated: 2024/07/15 17:38:35 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_printf(const char *string, ...);
void	form_spec_check(const char *string, va_list args, int *len);
void	is_pointer(size_t pointer, int *len);
void	is_char(char a, int *len);
void	is_string(char *s, int *len);
void	is_int(int num, char *str, int *len);
void	is_uint(unsigned int n, char *str, int *len);
void	is_shexa(unsigned int hexn, int *len);
void	is_bhexa(unsigned int hexn, int *len);

#endif
