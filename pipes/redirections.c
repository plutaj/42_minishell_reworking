/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:08:18 by huahmad           #+#    #+#             */
/*   Updated: 2025/06/25 15:18:12 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_heredoc(char *limiter)
{
    int pipefd[2];
    char *line;

    if (pipe(pipefd) == -1 || !limiter)
    {
        perror("syntax error near unexpected token `newline'");
        exit(-1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, limiter) == 0)
        {
            free(line);
            break;
        }
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);
    return (pipefd[0]);  // this should return read end to dup into stdin
}

static void opendup(int fd)
{
    if (fd == -1) perror("open error for >");
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2 error");
        close(fd);
        exit(1);
    }
    close(fd);
}

int redirectinp(t_data *data)
{
    int inpfrom;
    int fd;

    inpfrom = dup(STDIN_FILENO);
    if (inpfrom == -1) perror("dup");
    if (data->cmd_list->redir)
    {
        if (data->cmd_list->redir->type == REDIR_INPUT)
        {
            fd = open(data->cmd_list->redir->file_or_limiter, O_RDONLY);
            if (fd == -1) perror("open error");
            if (dup2(fd, STDIN_FILENO) == -1) perror("dup2 error");
            close(fd);
        }
        else if (data->cmd_list->redir->type == REDIR_HEREDOC)
        {
            fd = handle_heredoc(data->cmd_list->redir->file_or_limiter);
            if (fd == -1) return (-1);
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                close(fd);
                return (-1);
            }
            close(fd);
        }
    }
    return inpfrom;
}


int redirectout(t_data *data)
{
    int outto;
    int fd;

    outto = dup(STDOUT_FILENO); 
    if (outto == -1) perror("dup");
    if (data->cmd_list->redir)
    {
        if (data->cmd_list->redir->type == 1) // >
        {
            fd = open(data->cmd_list->redir->file_or_limiter, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            opendup(fd);
        }
        if (data->cmd_list->redir->type == 2) // >>
        {
            fd = open(data->cmd_list->redir->file_or_limiter, O_WRONLY | O_CREAT | O_APPEND, 0644);
            opendup(fd);
        }
    }
    return outto; // Original stdout for later restoration
}

    