/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:45:50 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/15 15:01:20 by huahmad          ###   ########.fr       */
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
	int from;
	int to;	
	
	from = redirectinp(cmd);
	to = redirectout(cmd);
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
			continue;
		}
		last_pid = fork_and_execute_pipe_cmd(data, cmd, &prev_pipe_read);
		cmd = cmd->next;
	}
	wait_for_children(last_pid);
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

void	is_my_external(t_data *data, t_command *cmd_list)
{
	char	*result;

	result = NULL;
	if (ft_strchr(cmd_list->args[0], '/'))
	{
		if (access(cmd_list->args[0], X_OK) == 0)
		{
			execerror(cmd_list->args[0], cmd_list->args, data->env);
			return ;
		}
	}
	else
		result = search_command_in_path(cmd_list, data);
	if (result)
	{
		execerror(result, cmd_list->args, data->env);
		free(result);
	}
	else
	{
		printf("minishell$: %s: command not found\n", cmd_list->args[0]);
		g_last_exit_status = 127;
		exit(g_last_exit_status);
	}
}
