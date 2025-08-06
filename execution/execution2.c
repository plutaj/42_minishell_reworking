/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:04:08 by jpluta            #+#    #+#             */
/*   Updated: 2025/08/06 14:46:56 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_process(pid_t pid)
{
	int	status;
	int	sig;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	if (WIFEXITED(status))
		g_last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		else if (sig == SIGINT)
			write(1, "\n", 1);
		g_last_exit_status = 128 + sig;
	}
}

int	execute_command(char *full_path, char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		child_process(full_path, args, env);
	else
		parent_process(pid);
	return (0);
}

void	exec_external_path(t_data *data, t_command *cmd)
{
	if (access(cmd->args[0], X_OK) == 0)
	{
		execerror(cmd->args[0], cmd->args, data->env);
		return ;
	}
}

void	exec_external_search(t_data *data, t_command *cmd)
{
	char	*result;

	result = search_command_in_path(cmd, data);
	if (result)
	{
		execute_command(result, cmd->args, data->env);
		free(result);
	}
	else
	{
		printf("minishell$: %s: command not found\n", cmd->args[0]);
		g_last_exit_status = 127;
		free_env(data->env);
		set_data_to_default(data);
		if (data->current_path)
			free(data->current_path);
		exit(g_last_exit_status);
	}
}
