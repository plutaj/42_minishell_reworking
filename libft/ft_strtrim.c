/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:29:01 by jpluta            #+#    #+#             */
/*   Updated: 2025/02/23 15:36:58 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set);

static int	check_set(char s, char const *set)
{
	size_t	i;

	i = 0;
	while (s != set[i] && set[i] != '\0')
		i++;
	if (set[i] == '\0')
		return (0);
	else
		return (1);
}

static char	*edge_cases(char const *s1, char const *set, char *str)
{
	if (!s1)
		return (NULL);
	if (!set)
	{
		str = malloc(1);
		str[0] = 0;
		return (str);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	start = 0;
	str = 0;
	edge_cases(s1, set, str);
	end = (ft_strlen(s1));
	while (s1[start] && (check_set(s1[start], set) == 1))
		start++;
	while (s1[end - 1] && (check_set(s1[end - 1], set) == 1))
		end--;
	if (start > end)
	{
		str = malloc(1);
		str[0] = 0;
	}
	else
		str = malloc((end - start) + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s1[start], ((end + 1) - start));
	return (str);
}

// int main(void)
// {
// 	printf("1 case:|%s|\n", ft_strtrim("", ""));
// 	// printf("\n");
// 	printf("2 case:|%s|\n", ft_strtrim(" ", ""));
// 	printf("3 case:|%s|\n", ft_strtrim("Hello, World!", " "));
// 	printf("4 case:|%s|\n", ft_strtrim(" Hello", " "));
// 	printf("5 case:|%s|\n", ft_strtrim("Hello ", " "));
// 	printf("6 case:|%s|\n", ft_strtrim(" Hello, World! ", " "));
// 	printf("7 case:|%s|\n", ft_strtrim("\t\n Hello, World! \r\n", " "));
// 	printf("8 case:|%s|\n", ft_strtrim("", NULL));
// 	printf("9 case:|%s|\n", ft_strtrim(" a ", " "));
// 	printf("10 case:|%s|\n", ft_strtrim("aaa", "a"));
// 	printf("11 case:|%s|\n", ft_strtrim(NULL, NULL));
// 	return (0);
// }
