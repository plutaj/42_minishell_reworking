/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:08:18 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/07 15:32:01 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int apply_regular_input(t_redir *redir, int saved_in)
{
    int fd;
	
	fd = open(redir->file_or_limiter, O_RDONLY);
    if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
    {
        perror("open or dup2 error");
        if (fd != -1) 
			close(fd);
        dup2(saved_in, STDIN_FILENO);
        close(saved_in);
        return (-1);
    }
    close(fd);
    return (0);
}
int apply_heredoc_input(t_redir *redir, int saved_in)
{
    int fd;
	
	fd = handle_heredoc(redir->file_or_limiter);
    if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
    {
        perror("heredoc error");
        if (fd != -1) close(fd);
        dup2(saved_in, STDIN_FILENO);
        close(saved_in);
        return (-1);
    }
    close(fd);
    return (0);
}

int apply_input_redir(t_redir *redir, int saved_in)
{
    if (redir->type == REDIR_INPUT)
        return apply_regular_input(redir, saved_in);
    else if (redir->type == REDIR_HEREDOC)
        return apply_heredoc_input(redir, saved_in);
    return (0);
}

int redirectinp(t_data *data)
{
    int saved_in;
    t_redir *redir;

	saved_in = dup(STDIN_FILENO);
	redir = data->cmd_list->redir;
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
                return (-1);
        }
        redir = redir->next;
    }
    return saved_in;
}

int apply_output_redir(t_redir *redir, int saved_out)
{
    int fd;
	
	if (redir->type == REDIR_HEREDOC)
		fd = open(redir->file_or_limiter, O_WRONLY | O_CREAT | O_APPEND);
	else if (redir->type == REDIR_OUTPUT)
		fd = open(redir->file_or_limiter, O_WRONLY| O_CREAT | O_TRUNC);
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

int redirectout(t_data *data)
{
    int saved_out = dup(STDOUT_FILENO);
    t_redir *redir = data->cmd_list->redir;

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
    return saved_out;
}


int heredoc_loop(int write_fd, char *limiter)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, limiter) == 0)
        {
            free(line);
            break;
        }
        if (write(write_fd, line, ft_strlen(line)) == -1 ||
            write(write_fd, "\n", 1) == -1)
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

int handle_heredoc(char *limiter)
{
    int pipefd[2];

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
    return pipefd[0];
}
