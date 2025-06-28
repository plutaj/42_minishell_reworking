/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:45:50 by huahmad           #+#    #+#             */
/*   Updated: 2025/06/28 11:05:57 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	executechild(t_data *data, t_command *cmd, int prev_pipe_read, int pipefd[]) 
{
	if (setup_redirection(prev_pipe_read, pipefd, cmd) == -1)
		perror("redirection");
    if (prev_pipe_read != STDIN_FILENO) close(prev_pipe_read);
	if (is_builtin(cmd))
		builtin(cmd);
	else
		is_external(data, cmd);
	exit(0);
}

void	executepipecmds(t_data *data)
{
	t_command	*cmd;
	int			pipefd[2];
	int			prev_pipe_read;
	pid_t		pid;

	cmd = data->cmd_list;
	prev_pipe_read = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next)
			if (pipe(pipefd) == -1) return (perror("pipe"));
		pid = fork();
		if (pid == -1) return (perror("fork"));
		if (pid == 0) executechild(data, cmd, prev_pipe_read, pipefd);
		// if (prev_pipe_read != STDIN_FILENO) close(prev_pipe_read);
		if (cmd->next)
		{
			close(pipefd[1]); 	
			prev_pipe_read = pipefd[0];
		}
		else
			close(pipefd[0]);
		waitpid(pid, NULL, 0);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0);
}

int setup_redirection(int prev_pipe_read, int pipefd[], t_command *cmd)
{
	if (prev_pipe_read != STDIN_FILENO)
		if (dup2(prev_pipe_read, STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
	if (cmd->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
	}
	close(pipefd[0]);
	return (0);
}
