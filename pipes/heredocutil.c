/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocutil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:16:10 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/21 16:47:26 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler_heredoc(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	close(STDIN_FILENO); 
	g_last_exit_status = 130;
}
