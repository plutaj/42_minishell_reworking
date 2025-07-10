/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inpredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:03:58 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/10 14:02:25 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*temp(int *fd, t_data *data)
{
	*fd = dup(STDOUT_FILENO);
	if (*fd == -1)
		perror("dup");
	return (data->cmd_list);
}

int	do_input_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_INPUT)
	{
		fd = open(redir->file_or_limiter, O_RDONLY);
		if (fd == -1)
			perror("open error");
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2 error");
		close(fd);
	}
	else if (redir->type == REDIR_HEREDOC)
	{
		fd = handle_heredoc(redir->file_or_limiter);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	apply_redirections(t_command *cmd)
{
	t_redir	*redir;
	int		in;
	int		out;

	redir = cmd->redir;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (in == -1 || out == -1)
		return (-1);
	while (redir)
	{
		if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
		{
			if (apply_input_redir(redir, in) == -1)
				return (-1);
		}
		else if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
		{
			if (apply_output_redir(redir, out) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	close(in);
	close(out);
	return (0);
}

int	has_input_redirection(t_command *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->type == REDIR_INPUT || r->type == REDIR_HEREDOC)
			return (1);
		r = r->next;
	}
	return (0);
}

int	has_output_redirection(t_command *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->type == REDIR_OUTPUT || r->type == REDIR_APPEND)
			return (1);
		r = r->next;
	}
	return (0);
}
