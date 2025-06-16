/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:38:50 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/16 19:15:12 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);    // couldnt compile on mac, uncomment before eval
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