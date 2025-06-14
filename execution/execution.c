/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:46:03 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/14 16:08:37 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execution(t_data *data)
{
    int         from;
    int         to;
    
    from = redirectinp(data);
    to = redirectout(data);
    if (from == -1) 
        exit(0);
    if (!data->cmd_list->next)
    {
        if (is_builtin(data->cmd_list))
			builtin(data->cmd_list);
		else
			is_external(data, data->cmd_list); 
    }
	else
        executepipecmds(data);
    if (dup2(from, STDIN_FILENO) == -1)
        perror("restore stdin");
    close(from);
    if (dup2(to, STDOUT_FILENO) == -1)
        perror("restore stdout");
    close(to);
}

char	*find_command_in_path(char	*cmd)
{
    char	*path_env;
	char	*path;
	char	**splited_path;
	int		i;
	
	i = 0;
	path_env = getenv("PATH");
	path = ft_strdup(path_env);
	if (!path)
        return (NULL);
	splited_path = ft_split(path, ':');
	free(path);
	while (splited_path[i])
	{
		path = concatenate_paths(splited_path[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
		{
            // Command found and executable, return full path
            free_2d_array(splited_path);  // Clean up split path array
            return (path);
        }
		free (path);
		i++;
	}
	free_2d_array(splited_path);
	return (NULL);
}

char	*concatenate_paths(char *dir, char *cmd)
{
    int		len;
	char	*full_path;
	
	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
    full_path = malloc(len);
    if (!full_path)
        return (NULL);
    ft_strcpy(full_path, dir);
    ft_strcat(full_path, "/");
    ft_strcat(full_path, cmd);
    return (full_path);
}

int	execute_command(char *full_path, char **args, char **env)
{
    pid_t	pid;
	int		status;
    int     sig;

	pid = fork();  // Create a new process
    if (pid == -1)
	{
        // If fork fails, handle error
        perror("fork");
        return -1;
    }

    if (pid == 0)
	{  // Child process
        // In the child process, execute the command
        if (execve(full_path, args, env) == -1)
		{
            perror("execve");
            exit(127);  // If execve fails, exit child process
        }
    } 
	else
	{
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            g_exit_status = WEXITSTATUS(status);  // Normal exit
        else if (WIFSIGNALED(status))
        {
            sig = WTERMSIG(status);
            if (sig == SIGQUIT)
                write(2, "Quit (core dumped)\n", 20);
            else if (sig == SIGINT)
                write(1, "\n", 1);
            g_exit_status = 128 + sig;  // Exit code from signal
        }
    }
    return 0;
}

// int	execute_command(char *full_path, char **args, char **env)
// {
//     pid_t	pid;
	
// 	pid = fork();  // Create a new process
//     if (pid == -1)
// 	{
//         // If fork fails, handle error
//         perror("fork");
//         return -1;
//     }

//     if (pid == 0)
// 	{  // Child process
//         // In the child process, execute the command
//         if (execve(full_path, args, env) == -1)
// 		{
//             perror("execve");
//             exit(127);  // If execve fails, exit child process
//         }
//     } 
// 	else
// 	{  // Parent process
//         int status;
//         waitpid(pid, &status, 0);  // Wait for the child process to finish
//         // if (WIFEXITED(status)) 
//         //     printf("Child process exited with status %d\n", WEXITSTATUS(status));
//     }
//     return 0;
// }
