/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:38:50 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/21 15:33:44 by huahmad          ###   ########.fr       */
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
