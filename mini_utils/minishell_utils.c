/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:38:50 by jpluta            #+#    #+#             */
/*   Updated: 2025/08/06 14:20:12 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	g_last_exit_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	only_spaces(const char *s)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (*str == ' ')
			str++;
		else
			return (0);
	}
	return (1);
}

void	cleanup_and_exit(t_data *data)
{
	perror("minishell: memory allocation failed");
	set_data_to_default(data);
	exit(EXIT_FAILURE);
}

bool	valid_input(char *input)
{
	int	i;

	i = 0;
	if (ft_strstr(input, "||") != NULL)
	{
		printf("bash: syntax error near unexpected token `||'\n");
		g_last_exit_status = 2;
		return (0);
	}
	if ((input[0] == '<' || input[0] == '>') && (!input[i + 1] || input[i
				+ 1] == ' '))
	{
		write(2, "parse error near `\\n'\n", 22);
		g_last_exit_status = 2;
		return (0);
	}
	if (input[0] == '|')
	{
		write(2, "parse error near `|'\n", 22);
		g_last_exit_status = 2;
		return (0);
	}
	return (1);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
