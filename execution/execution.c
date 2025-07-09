/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:46:03 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/09 19:06:34 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_data *data)
{
	int	from;
	int	to;
	int saved_in;
	int saved_out;

	if (!data->cmd_list->next)
	{
		from = redirectinp(data->cmd_list);
		to = redirectout(data->cmd_list);
		saved_in = dup(STDIN_FILENO);
		saved_out = dup(STDOUT_FILENO);
		if (is_builtin(data->cmd_list))
			builtin(data->cmd_list);
		else
			is_external(data, data->cmd_list);
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		if (from != -1) close(from);
		if (to != -1) close(to);
	}
	else
		executepipecmds(data);
}

static void	child_process(char *full_path, char **args, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(full_path, args, env) == -1)
	{
		perror("execve");
		exit(126);
	}
}

static void	parent_process(pid_t pid)
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
