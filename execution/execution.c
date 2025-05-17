/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:46:03 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/17 15:21:47 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execution(t_data *data)
{
    // One command case (0 pipes)
    if (!data->cmd_list->next)
    {
        if (is_builtin(data->cmd_list))
			builtin(data->cmd_list);
		else
			is_external(data, data->cmd_list); 
    }
	// More command case (with pipes)
	// else
	// {
		
	// }
}

int is_builtin(t_command *cmd_list)
{
    if (ft_strcmp("echo", cmd_list->args[0]) == 0)
		return (1);
    else if (ft_strcmp("cd", cmd_list->args[0]) == 0)
        return (1);
    else if (ft_strcmp("pwd", cmd_list->args[0]) == 0)
        return (1);
    else if (ft_strcmp("export", cmd_list->args[0]) == 0)
        return (1);
    else if (ft_strcmp("unset", cmd_list->args[0]) == 0)
        return (1);
    else if (ft_strcmp("env", cmd_list->args[0]) == 0)
        return (1);
    else if (ft_strcmp("exit", cmd_list->args[0]) == 0)
        return (1);
    return (0);
}

void is_external(t_data *data, t_command *cmd_list)
{
	char	*result;

	result = NULL;
    if (ft_strchr(cmd_list->args[0], '/'))
    {
        if (access(cmd_list->args[0], X_OK) == 0)
            printf("found in path /"); // fork and exec
    } 
    else
    {
        // search cmd in each $PATH entry:
		result = find_command_in_path(cmd_list->args[0]);
    }
    if (result)
	{
		execute_command(result, cmd_list->args, data->env);
		free(result);
	}
    else
	{
		printf("minishell$: %s: command not found\n", cmd_list->args[0]);
		exit(1);
	}
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
            exit(1);  // If execve fails, exit child process
        }
    } 
	else
	{  // Parent process
        int status;
        waitpid(pid, &status, 0);  // Wait for the child process to finish
        // if (WIFEXITED(status)) 
        //     printf("Child process exited with status %d\n", WEXITSTATUS(status));
    }

    return 0;
}