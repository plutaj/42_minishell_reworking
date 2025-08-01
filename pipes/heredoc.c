/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:06:49 by jpluta            #+#    #+#             */
/*   Updated: 2025/08/01 15:43:32 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_loop(int write_fd, char *limiter)
{
	char	*line;

	signal(SIGINT, sigint_handler_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		if (write(write_fd, line, ft_strlen(line)) == -1 || write(write_fd,
				"\n", 1) == -1)
		{
			perror("write error");
			free(line);
			close(write_fd);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	handle_heredoc(char *limiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1 || !limiter)
	{
		perror("syntax error near unexpected token `newline'");
		return (-1);
	}
	if (heredoc_loop(pipefd[1], limiter) == -1)
	{
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	redirectinp(t_command *cmd_list)
{
	int		saved_in;
	t_redir	*redir;

	saved_in = dup(STDIN_FILENO);
	redir = cmd_list->redir;
	if (saved_in == -1)
	{
		perror("dup");
		return (-1);
	}
	while (redir)
	{
		if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
		{
			if (apply_input_redir(redir, saved_in) == -1)
			{
				close(saved_in);
				return (-1);
			}
		}
		redir = redir->next;
	}
	close(saved_in);
	return (saved_in);
}

void	execerror(char *full_path, char **args, char **env)
{
	execve(full_path, args, env);
	perror("execve");
	exit(127);
}

t_command	*temp(int *fd, t_data *data)
{
	*fd = dup(STDOUT_FILENO);
	if (*fd == -1)
		perror("dup");
	return (data->cmd_list);
}
