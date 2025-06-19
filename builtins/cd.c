/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:06:54 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/19 16:44:57 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cmd_cd(t_data *data)
{
	char *new_path;
	
	// case "cd"
	if (data->cmd_list->args[2])
	{
		printf("minishell: cd: too many arguments\n");
		g_last_exit_status = 1;
	}
	else if (!data->cmd_list->args[1])
	{
		chdir(is_env_var("$HOME", data->env));
		free(data->current_path);
		data->current_path = ft_strdup(is_env_var("$HOME", data->env));
	}
	// case "cd .."
	else if (ft_strcmp(data->cmd_list->args[1], "..") == 0)
	{
		if (count_slash(data->current_path) > 1 && data->current_path && data->current_path[0] != '\0')
		{
			// Remove the last directory from current_path
			char *last_slash = strrchr(data->current_path, '/');
			if (last_slash && count_slash(data->current_path) > 1)
				*last_slash = '\0';  // Null-terminate the path at the last slash
			new_path = ft_strdup(data->current_path);  // Copy the updated path
			if (chdir(new_path) == 0)
			{
				free(data->current_path);  // Free old path
				data->current_path = new_path;  // Update current path
			}
			else
			{
				perror("cd 2");
				g_last_exit_status = 1;
				free(new_path);  // Free new_path if chdir fails
			}
		}
	}
	// case "cd dir"
	else if (data->cmd_list)
		cmd_cd_dir(data);
}

void	cmd_cd_dir(t_data *data)
{
	char	*original_path;
	char	**temp;
	char	*temp_path;
	int		i;

	original_path = ft_strdup(data->current_path); // dont forget to free if not used
	temp = ft_split(data->cmd_list->args[1], '/');
	i = 0;
	while (temp[i])
	{
		if (list_directory_contents(temp[i], original_path))
		{
			temp_path = append_char_to_str(original_path, '/');
			free(original_path);
			original_path = temp_path;
			temp_path = ft_strjoin(original_path, temp[i]);
			if (chdir(temp_path) == 0)
			{
				free(original_path);
				original_path = temp_path;
			}
			else
			{
				free(original_path);
				free(temp_path);
				free_2d_array(temp);
				perror("cd 3");
				return ;
			}
		}
		else
		{
			printf("minishell: cd: %s No such file or directory\n", data->cmd_list->args[1]);
			g_last_exit_status = 1;
			return ;
		}
		i++;
	}
	free_2d_array(temp);
	free(data->current_path);
	data->current_path = original_path;
}

int count_slash(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '/')
			count++;
		str++;
	}
	return (count);
}

int list_directory_contents(char *str, const char *path)
{
    struct dirent	*entry;
    DIR 			*dp;
	
	dp = opendir(path);
    if (dp == NULL)
	{
        perror("opendir");
        exit(1);
    }
    while ((entry = readdir(dp)) != NULL)
	{
        if (ft_strcmp(str, entry->d_name) == 0)
		{
			closedir(dp);
			return (1);
		}
    }
    closedir(dp);
	return (0);
}

char    *append_char_to_str(char *str, char c)
{
	size_t 	len;
	char 	*new_str;
	
	if (!str)
	{
		char *new_str = malloc(2); // one char + null terminator
		if (!new_str) return NULL;
		new_str[0] = c;
		new_str[1] = '\0';
		return new_str;
	}
	len = ft_strlen(str);
	new_str = malloc(len + 2); // existing string + new char + null terminator
	if (!new_str) return NULL;
	ft_strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}