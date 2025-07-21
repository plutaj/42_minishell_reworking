/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocutil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:16:10 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/21 17:42:39 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler_heredoc(int signo)
{
	(void)signo;
	write(1, "^C\n", 4);
	close(STDIN_FILENO); 
	g_last_exit_status = 130;
}
