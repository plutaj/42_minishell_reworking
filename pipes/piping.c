/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:45:50 by huahmad           #+#    #+#             */
/*   Updated: 2025/05/22 12:12:38 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	executepipecmds2(t_data *data)
// {
//     t_command	*cmd;
//     int			pipefd[2]; 
//     int			prev_pipe_read; 
//     pid_t		pid;
    
//     cmd = data->cmd_list;
//     prev_pipe_read = 0; // input
//     while (cmd)
//     {
//         if (pipe(pipefd) == -1)
//         {
//             perror("error pipe");
//             return ;
//         }
//         pid = fork();
//         if (pid == -1)
//         {
//             perror("error fork");
//             return ;
//         }
//         if (pid == 0)
//             childprocess(data, pipefd, prev_pipe_read);
//         waitpid(pid, NULL, 0);
//         parentprocess(data, pipefd, prev_pipe_read);
//     }
// }

// void parentprocess(t_data *data, int *fd, int prev_pipe_read)
// {
//     close(prev_pipe_read);  // Close the previous read end
//     dup2(fd[0], STDIN_FILENO);
//     if (data->cmd_list->next)
//     {
//         close(fd[1]);  // Close the write end of the current pipe
//         prev_pipe_read = fd[0];  // Save the read end for the next command
//     }
//     else
//         close(fd[0]);
// }

// void childprocess(t_data *data, int *fd, int prev_pipe_read)
// {
//     if (prev_pipe_read != STDIN_FILENO)
//     {
//         dup2(prev_pipe_read, STDIN_FILENO);
//         close(prev_pipe_read);
//     }
//     //int filein and the open for redirection
//     dup2(fd[1], 1);
//     // if (filein)
//     //{
//         //dup2(filein, 0);
//         //close(0);
//     //}    
//     if (is_builtin(data->cmd_list))
//         builtin(data->cmd_list);
//     else
//         is_external(data, data->cmd_list);
//     exit(0);
// }


    // void	executepipecmds(t_data *data)
    // {
    //     t_command	*cmd;
    //     int			pipefd[2]; 
    //     int			prev_pipe_read; 
    //     pid_t		pid;
    //     cmd = data->cmd_list;
    //     prev_pipe_read = STDIN_FILENO;  // Initially, read from standard input
    //     while (cmd)
    //     {
    //         if (cmd->next)
    //         {
    //             if (pipe(pipefd) == -1)
    //             {
    //                 perror("pipe");
    //                 return ;
    //             }
    //         }
    //         pid = fork();
    //         if (pid == -1)
    //         {
    //             perror("fork");
    //             return ;
    //         }
    //         if (pid == 0)
    //         {  // Child process
    //             if (prev_pipe_read != STDIN_FILENO)
    //             {
    //                 dup2(prev_pipe_read, STDIN_FILENO);
    //                 close(prev_pipe_read);
    //             }
    //             // Redirect output to the next command (if not the last command)
    //             if (cmd->next)
    //             {
    //                 dup2(pipefd[1], STDOUT_FILENO);
    //                 // close(pipefd[1]);
    //                 close(pipefd[0]);
    //             }
    //             // Execute the command
    //             if (is_builtin(cmd))
    //                 builtin(cmd);
    //             else
    //             {
    //                 char *full_path;
    //                 full_path = NULL;
    //                 if (ft_strchr(cmd->args[0], '/'))
    //                 {
    //                     if (access(cmd->args[0], X_OK) == 0)
    //                     {
    //                         full_path = ft_strdup(cmd->args[0]);
    //                     }
    //                 }
    //                 else
    //                     full_path = find_command_in_path(cmd->args[0]);
    //                 if (full_path)
    //                 {
    //                     execute_command(full_path, cmd->args, data->env);
    //                     free(full_path);
    //                 }
    //                 else
    //                 {
    //                     printf("minishell: command not found: %s\n", cmd->args[0]);
    //                     exit(1);
    //                 }
    //             }
    //             exit(0);
    //         }
    //         else
    //         {  // Parent process
    //             close(prev_pipe_read);  // Close the previous read end
    //             dup2(pipefd[0], STDIN_FILENO);
    //             if (cmd->next)
    //             {
    //                 close(pipefd[1]);  // Close the write end of the current pipe
    //                 prev_pipe_read = pipefd[0];  // Save the read end for the next command
    //             }
    //             else
    //                 close(pipefd[0]);
    //             waitpid(pid, NULL, 0);  // Wait for the child process to finish
    //         }
    //         cmd = cmd->next;
    //     }
    //     // Wait for all child processes to complete
    //     while (wait(NULL) > 0);
    // }


// void	executepipecmds3(t_data *data)
// {
//     t_command   *cmd;
//     int         fd[2];
//     int         prev_pipe_read;
//     pid_t       pid;    

//     cmd = data->cmd_list;
//     prev_pipe_read = STDIN_FILENO; // which is zero
//     while (cmd)
//     {
//         if (is_builtin(cmd))
//         {
//             if (prev_pipe_read != STDIN_FILENO)
//             {
//                 dup2(prev_pipe_read, STDIN_FILENO);
//                 close(prev_pipe_read);
//             }
//             builtin(cmd);
//             cmd = cmd->next;
//         }
//         if (cmd->next && !is_builtin(cmd->next))
//         {
//             if (pipe(fd) == -1)
//             {
//                 perror("pipe error");
//                 return ;
//             }
//             pid = fork();
//         }
//     }
// }


void	executepipecmds(t_data *data)
{
	t_command	*cmd;
	int			pipefd[2];
	int			prev_pipe_read;
	pid_t		pid;

	cmd = data->cmd_list;
	prev_pipe_read = STDIN_FILENO;
	while (cmd)
	{
		if (is_builtin(cmd))
		{
			if (prev_pipe_read != STDIN_FILENO)
			{
				if (dup2(prev_pipe_read, STDIN_FILENO))
                    printf("dup2");
				close(prev_pipe_read);
			}
			builtin(cmd);
			cmd = cmd->next;
			continue ;
		}
        if (cmd == NULL) cmd = cmd->next;
		if (cmd->next && !is_builtin(cmd->next))
			if (pipe(pipefd) == -1)
				return (perror("pipe"), (void)0);
		pid = fork();
        // printf("this should print twice\n");
		if (pid == -1)
			return (perror("fork"), (void)0);
		if (pid == 0)
		{
			if (setup_redirection(prev_pipe_read, pipefd, cmd) == -1)
				exit(1);
			execute_child_process(data, cmd);
		}
		close(prev_pipe_read);
		if (cmd->next && !is_builtin(cmd->next))
		{
			close(pipefd[1]); //because the parant doesn't write to the pipe
			prev_pipe_read = pipefd[0];
		}
		else
			close(pipefd[0]);
		waitpid(pid, NULL, 0);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0) ;
}

int setup_redirection(int prev_pipe_read, int pipefd[], t_command *cmd)
{
	if (prev_pipe_read != STDIN_FILENO)
	{
		if (dup2(prev_pipe_read, STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
	}
	if (cmd->next && !is_builtin(cmd->next))
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
		close(pipefd[1]);
		close(pipefd[0]);
	}
    return (0);
}

void	execute_child_process(t_data *data, t_command *cmd)
{
	char	*full_path;

	full_path = NULL;
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], X_OK) == 0)
			full_path = ft_strdup(cmd->args[0]);
	}
	else
		full_path = find_command_in_path(cmd->args[0]);
	if (full_path)
	{
		execute_command(full_path, cmd->args, data->env);
		free(full_path);
	}
	else
		printf("minishell: command not found: %s\n", cmd->args[0]);
}
