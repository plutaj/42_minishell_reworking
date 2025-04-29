/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:32:05 by jpluta            #+#    #+#             */
/*   Updated: 2024/06/08 17:01:32 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// void	ft_print_result(char const *s)
// {
// 	int		len;

// 	len = 0;
// 	while (s[len])
// 		len++;
// 	write(1, s, len);
// }

// char	mapi(unsigned int i, char c)
// {
// 	static int indexArray[11] = {0};

// 	if (i > 10 || indexArray[i] == 1)
// 		write(1, "wrong index\n", 12);
// 	else
// 		indexArray[i] = 1;
// 	if (c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	else if (c >= 'A' && c <= 'Z')
// 		return (c + 32);
// 	else
// 		return (c);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*str;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	str = (char *)malloc((len + 1) * (sizeof(char)));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/* funkcia ktora aplikuje funkciu 'f' na kazdy charakter
stringu 's' (funkcia vrati novy modifikovany string) */

// int main()
// {
// 	char *s = "LoReM iPsUm";
// 	char *s1 = ft_strmapi(s, mapi);
// 	printf("%s\n", s1);
// 	return (0);
// }

// int main(void)
// {
// 	char	*str;
// 	char	*strmapi;

// 	alarm(5);
// 	str = (char *)malloc(sizeof(*str) * 12);
// 	strcpy(str, "LoReM iPsUm");
// 	strmapi = ft_strmapi(str, &mapi);
// 	ft_print_result(strmapi);
// 	if (strmapi == str)
// 		ft_print_result("\nA new string was not returned");
// 	if (strmapi[11] != '\0')
// 		ft_print_result("\nString is not null terminated");
// 	return (0);
// }
