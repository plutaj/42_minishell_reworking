/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:45:50 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/01 16:38:15 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	closeiferror(int from, int to)
{
	if (from == -1)
		close(from);
	if (to == -1)
		close(to);
}

static void	handle_child_process(t_data *data, t_command *cmd,
		int prev_pipe_read, int pipefd[2])
{
	int	from;
	int	to;

	from = redirectinp(cmd);
	to = redirectout(cmd);
	if (errorfromto(from, to, prev_pipe_read, pipefd[1]))
	{
		closeiferror(from, to);
		set_data_to_default(data);
		free_env(data->env);
		if (data->current_path)
			free(data->current_path);
		data->current_path = NULL;
		exit(EXIT_FAILURE);
	}
	closeiferror(from, to);
	executechild(data, cmd, prev_pipe_read, pipefd);
}

pid_t	fork_and_execute_pipe_cmd(t_data *data, t_command *cmd,
		int *prev_pipe_read)
{
	int		pipefd[2];
	pid_t	pid;

	pipefd[0] = -1;
	pipefd[1] = -1;
	if (cmd->next && create_pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		handle_child_process(data, cmd, *prev_pipe_read, pipefd);
	update_pipe_fds(prev_pipe_read, pipefd, cmd->next != NULL);
	return (pid);
}

void	executepipecmds(t_data *data)
{
	t_command	*cmd;
	int			prev_pipe_read;
	pid_t		last_pid;

	last_pid = -1;
	cmd = data->cmd_list;
	prev_pipe_read = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->parseerror)
		{
			g_last_exit_status = 2;
			cmd = cmd->next;
			continue ;
		}
		last_pid = fork_and_execute_pipe_cmd(data, cmd, &prev_pipe_read);
		cmd = cmd->next;
	}
	wait_for_children(last_pid);
}

void	is_my_external(t_data *data, t_command *cmd_list)
{
	if (ft_strchr(cmd_list->args[0], '/'))
		exec_external_path(data, cmd_list);
	else
		exec_external_search(data, cmd_list);
}
