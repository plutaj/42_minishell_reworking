/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocutil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:16:10 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/22 12:26:43 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler_heredoc(int signo)
{
	(void)signo;
	g_last_exit_status = 130;
	write(1, "^C", 2);
	close(STDIN_FILENO); 
}
