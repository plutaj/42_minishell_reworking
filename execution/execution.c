/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:46:03 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/21 18:09:43 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	dup2andclose(int savedin, int savedout)
{
	dup2(savedin, STDIN_FILENO);
	dup2(savedout, STDOUT_FILENO);
	close(savedin);
	close(savedout);
}

bool	errorfromto(int from, int to, int saved_in, int saved_out)
{
	if (from == -1 || to == -1)
	{
		dup2andclose(saved_in, saved_out);
		g_last_exit_status = 1;
		return (true);
	}
	return (false);
}

bool	all_cmds_invalid(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd_list;
	while (cmd)
	{
		if (!cmd->parseerror)
			return (false);
		cmd = cmd->next;
	}
	return (true);
}

void	execution(t_data *data)
{
	int	from;
	int	to;
	int	saved_in;
	int	saved_out;

	if (!data->cmd_list->next)
	{
		saved_in = dup(STDIN_FILENO);
		saved_out = dup(STDOUT_FILENO);
		from = redirectinp(data->cmd_list);
		to = redirectout(data->cmd_list);
		if (errorfromto(from, to, saved_in, saved_out))
			return ;
		if (is_builtin(data->cmd_list))
			builtin(data->cmd_list);
		else
			is_external(data, data->cmd_list);
		if (from != -1)
			close(from);
		if (to != -1)
			close(to);
		dup2andclose(saved_in, saved_out);
	}
	else
		executepipecmds(data);
}

void	child_process(char *full_path, char **args, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(full_path, args, env) == -1)
	{
		perror("execve");
		exit(126);
	}
}
