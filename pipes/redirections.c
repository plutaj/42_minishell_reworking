/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:08:18 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/01 17:27:59 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	apply_regular_input(t_redir *redir, int saved_in)
{
	int	fd;

	fd = open(redir->file_or_limiter, O_RDONLY);
	if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
	{
		perror("open or dup2 error");
		if (fd != -1)
			close(fd);
		dup2(saved_in, STDIN_FILENO);
		g_last_exit_status = 1;
		close(saved_in);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_heredoc_input(t_redir *redir, int saved_in)
{
	int	fd;

	fd = handle_heredoc(redir->file_or_limiter);
	if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
	{
		perror("heredoc error");
		if (fd != -1)
			close(fd);
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
		g_last_exit_status = 1;
		exit(1);
	}
	close(fd);
	return (0);
}

int	apply_input_redir(t_redir *redir, int saved_in)
{
	int fd;
	
	if (redir->type == REDIR_INPUT)
	{
		fd = open(redir->file_or_limiter, O_RDONLY);
		if (fd == -1)
		{
			perror("open error");
			g_last_exit_status = 1;
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_HEREDOC)
		return (apply_heredoc_input(redir, saved_in));
	return (0);
}

int	apply_output_redir(t_redir *redir, int saved_out)
{
	int	fd;

	fd = 0;
	if (redir->type == REDIR_APPEND)
		fd = open(redir->file_or_limiter, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == REDIR_OUTPUT)
		fd = open(redir->file_or_limiter, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
	{
		perror("Invalid redirection type\n");
		return (-1);
	}
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("open or dup2 error");
		if (fd != -1)
			close(fd);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirectout(t_command *cmd_list)
{
	int		saved_out;
	t_redir	*redir;

	saved_out = dup(STDOUT_FILENO);
	redir = cmd_list->redir;
	if (saved_out == -1)
	{
		perror("dup");
		return (-1);
	}
	while (redir)
	{
		if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
		{
			if (apply_output_redir(redir, saved_out) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	close(saved_out);
	return (saved_out);
}
