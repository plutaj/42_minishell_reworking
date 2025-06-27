/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:08:18 by huahmad           #+#    #+#             */
/*   Updated: 2025/06/27 15:10:56 by huahmad          ###   ########.fr       */
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
    if (fd == -1)
    {
        perror("open error for >");
        exit(1);
    }
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

    inpfrom = dup(STDIN_FILENO);
    if (inpfrom == -1) perror("dup");
    if (data->cmd_list->redir)
        if (do_input_redir(data->cmd_list->redir) == -1)
            return -1;
    return inpfrom;
}

int redirectout(t_data *data)
{
    int outto;
    int fd; 
    t_command *cmd_list_copy;

    cmd_list_copy = temp(&outto, data);
    while (cmd_list_copy)
    {   
        if (cmd_list_copy->redir)
        {
            if (cmd_list_copy->redir->type == 1) // >
            {
                fd = open(cmd_list_copy->redir->file_or_limiter, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                opendup(fd);
            }
            if (cmd_list_copy->redir->type == 2) // >>
            {
                fd = open(cmd_list_copy->redir->file_or_limiter, O_WRONLY | O_CREAT | O_APPEND, 0644);
                opendup(fd);
            }
        }
        cmd_list_copy = cmd_list_copy->next;
    }
    return outto; // Original stdout for later restoration
}
