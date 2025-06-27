/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:29:05 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/27 17:29:07 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command*  temp(int *fd, t_data *data)
{
    *fd = dup(STDOUT_FILENO);
    if (*fd == -1) perror("dup");
    return (data->cmd_list);
}

int do_input_redir(t_redir *redir)
{
    int fd;

    if (redir->type == REDIR_INPUT)
    {
        fd = open(redir->file_or_limiter, O_RDONLY);
        if (fd == -1) perror("open error");
        if (dup2(fd, STDIN_FILENO) == -1) perror("dup2 error");
        close(fd);
    }
    else if (redir->type == REDIR_HEREDOC)
    {
        fd = handle_heredoc(redir->file_or_limiter);
        if (fd == -1) return -1;
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            close(fd);
            return -1;
        }
        close(fd);
    }
    return 0;
}