/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:28:30 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/09 19:29:36 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_children(void)
{
	while (wait(NULL) > 0)
		;
}

void	executechild(t_data *data, t_command *cmd, int prev_pipe_read, int pipefd[])
{
	if (apply_redirections(cmd) == -1)
		perror("redirection");
	if (setup_redirection(prev_pipe_read, pipefd, cmd) == -1)
		perror("pipe dup");
	if (prev_pipe_read != STDIN_FILENO)
		close(prev_pipe_read);
	if (is_builtin(cmd))
		builtin(cmd);
	else
		is_my_external(data, cmd);
	exit(1);
}
