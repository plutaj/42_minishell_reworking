/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:45:50 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/09 17:06:09 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_for_children(void)
{
	while (wait(NULL) > 0)
		;
}

static void	executechild(t_data *data, t_command *cmd, int prev_pipe_read,
		int pipefd[])
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
		if (cmd->next && create_pipe(pipefd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
			executechild(data, cmd, prev_pipe_read, pipefd);
		update_pipe_fds(&prev_pipe_read, pipefd, cmd->next != NULL);
		cmd = cmd->next;
	}
	wait_for_children();
}

int	setup_redirection(int prev_pipe_read, int pipefd[], t_command *cmd)
{
	if (prev_pipe_read != STDIN_FILENO  && !has_input_redirection(cmd))
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
