/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:06:54 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/03 16:26:26 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cmd_cd_dir2(t_data *data, char **temp, char **original_path, int i);
static void	err_no_such_file(void);

static void	handle_cd_dotdot(t_data *data)
{
	char	*last_slash;
	char	*new_path;

	if (count_slash(data->current_path) <= 1 || !data->current_path
		|| !data->current_path[0])
		return ;
	last_slash = strrchr(data->current_path, '/');
	if (last_slash && count_slash(data->current_path) > 1)
		*last_slash = '\0';
	new_path = ft_strdup(data->current_path);
	if (chdir(new_path) == 0)
	{
		free(data->current_path);
		data->current_path = new_path;
		update_env_var(data->env, "PWD", new_path);
		g_last_exit_status = 0;
	}
	else
	{
		perror("cd 2");
		g_last_exit_status = 1;
		free(new_path);
	}
}

void	cmd_cd(t_data *data)
{
	if (data->cmd_list->args[2])
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
		g_last_exit_status = 1;
	}
	else if (!data->cmd_list->args[1])
	{
		chdir(is_env_var("$HOME", data->env));
		if (data->current_path)
			free(data->current_path);
		data->current_path = ft_strdup(is_env_var("$HOME", data->env));
		update_env_var(data->env, "PWD", data->current_path);
		g_last_exit_status = 0;
	}
	else if (ft_strcmp(data->current_path, data->cmd_list->args[1]) == 0)
	{
		write(STDOUT_FILENO, "binary file matches\n", 19);
		g_last_exit_status = 0;
	}
	else if (ft_strcmp(data->cmd_list->args[1], "..") == 0)
		handle_cd_dotdot(data);
	else
		cmd_cd_dir(data);
}

void	cmd_cd_dir(t_data *data)
{
	char	*original_path;
	char	**temp;
	int		i;

	original_path = ft_strdup(data->current_path);
	temp = ft_split(data->cmd_list->args[1], '/');
	i = 0;
	while (temp[i])
	{
		if (list_directory_contents(temp[i], original_path))
		{
			cmd_cd_dir2(data, temp, &original_path, i);
			if (g_last_exit_status == 1)
				break ;
		}
		else
		{
			err_no_such_file();
			break ;
		}
		i++;
	}
	if (temp[i] == NULL && g_last_exit_status == 0)
	{
		if (data->current_path)
			free(data->current_path);
		data->current_path = original_path;
		update_env_var(data->env, "PWD", original_path);
		free_2d_array(temp);
	}
	else
	{
		free_2d_array(temp);
		free (original_path);
	}
}

static void	cmd_cd_dir2(t_data *data, char **temp, char **original_path, int i)
{
	char	*temp_path;
	char	*tmp;

	(void)data;
	tmp = append_char_to_str(*original_path, '/');
	free(*original_path);
	*original_path = tmp;
	temp_path = ft_strjoin(*original_path, temp[i]);
	if (chdir(temp_path) == 0)
	{
		free(*original_path);
		*original_path = temp_path;
		g_last_exit_status = 0;
	}
	else
	{
		free(*original_path);
		free(temp_path);
		g_last_exit_status = 1;
		perror("cd 3");
	}
}

static void	err_no_such_file(void)
{
	write(STDERR_FILENO, " No such file or directory\n", 28);
	g_last_exit_status = 1;
}