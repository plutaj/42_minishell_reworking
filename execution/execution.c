/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:46:03 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/03 13:28:11 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static char *search_in_paths(char **splited_path, char *cmd);

void	execution(t_data *data)
{
	int	from;
	int	to;

	from = redirectinp(data);
	to = redirectout(data);
	if (from == -1)
		exit(0);
	if (!data->cmd_list->next)
	{
		if (is_builtin(data->cmd_list))
			builtin(data->cmd_list);
		else
			is_external(data, data->cmd_list);
	}
	else
		executepipecmds(data);
	if (dup2(from, STDIN_FILENO) == -1)
		perror("restore stdin");
	close(from);
	if (dup2(to, STDOUT_FILENO) == -1)
		perror("restore stdout");
	close(to);
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
