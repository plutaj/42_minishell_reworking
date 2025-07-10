/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:45:50 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/10 13:10:42 by huahmad          ###   ########.fr       */
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

void	fork_and_execute_pipe_cmd(t_data *data, t_command *cmd,
		int *prev_pipe_read)
{
	int		pipefd[2];
	pid_t	pid;
	int		from;
	int		to;

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
	{
		from = redirectinp(cmd);
		to = redirectout(cmd);
		closeiferror(from, to);
		executechild(data, cmd, *prev_pipe_read, pipefd);
	}
	update_pipe_fds(prev_pipe_read, pipefd, cmd->next != NULL);
}

void	executepipecmds(t_data *data)
{
	t_command	*cmd;
	int			prev_pipe_read;

	cmd = data->cmd_list;
	prev_pipe_read = STDIN_FILENO;
	while (cmd)
	{
		fork_and_execute_pipe_cmd(data, cmd, &prev_pipe_read);
		cmd = cmd->next;
	}
	wait_for_children();
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
	close(pipefd[0]);
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
	{
		result = search_command_in_path(cmd_list, data);
	}
	if (result)
	{
		execerror(result, cmd_list->args, data->env);
		free(result);
	}
	else
	{
		printf("minishell$: %s: command not found\n", cmd_list->args[0]);
		g_last_exit_status = 127;
	}
}
