/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:28:30 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/28 13:47:13 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		closeiferror(int pipefd[2], int prev_pipe_read)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	if (prev_pipe_read != STDIN_FILENO)
		close(prev_pipe_read);
}

void	wait_for_children(pid_t last_pid)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				g_last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_last_exit_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
}

void	executechild(t_data *data, t_command *cmd, int prev_pipe_read,
		int pipefd[])
{
	if (apply_redirections(cmd) == -1)
		perror("redirection");
	if (setup_redirection(prev_pipe_read, pipefd, cmd) == -1)
		perror("pipe dup");
	closeiferror(pipefd, prev_pipe_read);
	if (is_builtin(cmd))
	{
		builtin(cmd);
		free_env(data->env);
		set_data_to_default(data);
		if (data->current_path)
			free(data->current_path);
		data->current_path = NULL;
		exit(g_last_exit_status);
	}
	else
	{
		is_my_external(data, cmd);
		free_env(data->env);
		set_data_to_default(data);
		exit(g_last_exit_status);
	}
	exit(1);
}

int	setup_redirection(int prev_pipe_read, int pipefd[], t_command *cmd)
{
	if (prev_pipe_read != STDIN_FILENO && !has_input_redirection(cmd))
		if (dup2(prev_pipe_read, STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
	if (cmd->next && !has_output_redirection(cmd))
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
	}
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	return (0);
}

