/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:08:18 by huahmad           #+#    #+#             */
/*   Updated: 2025/06/09 16:00:31 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	redirect(t_data *data)
// {
//     int         orig_stdin;
	
//     orig_stdin = dup(STDIN_FILENO);
// 	if (orig_stdin == -1) exit(EXIT_FAILURE);

// 	if (dup2(orig_stdin, STDIN_FILENO) == -1) exit(EXIT_FAILURE);
//     close(orig_stdin);
// }

int	redirectinp(t_data *data)
{
	int inpfrom;
    int fd;

	inpfrom = dup(STDIN_FILENO);
    if (inpfrom == -1) perror("dup");
	if (data->cmd_list->redir)
    {
        if (data->cmd_list->redir->type == 0)
        {
            fd = open(data->cmd_list->redir->file_or_limiter, O_RDONLY);
            if (fd == -1) perror("open error");
            if (dup2(fd, STDIN_FILENO) == -1) 
            {
                close(fd);
                return (-1);
            }
            close(fd);
        }
    }
    return (inpfrom);
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
            if (fd == -1) perror("open error for >");
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("dup2 error");
                close(fd);
                return -1;
            }
            close(fd);
        }
        else if (data->cmd_list->redir->type == 2) // >>
        {
            fd = open(data->cmd_list->redir->file_or_limiter, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)   perror("open error for >>");
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("dup2 error");
                close(fd);
                return -1;
            }
            close(fd);
        }
    }
    return outto; // Original stdout for later restoration
}

    