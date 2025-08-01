/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:06:54 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/08/01 16:46:17 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	cd_absolute_or_home(t_data *data)
{
	if (!data->cmd_list->args[1])
	{
		chdir(is_env_var("$HOME", data->env));
		if (data->current_path)
			free(data->current_path);
		data->current_path = ft_strdup(is_env_var("$HOME", data->env));
		update_env_var(data->env, "PWD", data->current_path);
		g_last_exit_status = 0;
	}
	else if (data->cmd_list->args[1][0] == '/')
	{
		if (chdir(data->cmd_list->args[1]) == 0)
		{
			if (data->current_path)
				free(data->current_path);
			data->current_path = ft_strdup(data->cmd_list->args[1]);
			update_env_var(data->env, "PWD", data->current_path);
			g_last_exit_status = 0;
		}
		else
		{
			perror("cd");
			g_last_exit_status = 1;
		}
	}
}

void	cmd_cd(t_data *data)
{
	if (data->cmd_list->args[2])
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
		g_last_exit_status = 1;
	}
	else if (!data->cmd_list->args[1] || data->cmd_list->args[1][0] == '/')
		cd_absolute_or_home(data);
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

static void	cd_dir_loop(t_data *data, char **temp, char **original_path, int *i)
{
	while (temp[*i])
	{
		if (list_directory_contents(temp[*i], *original_path))
		{
			cmd_cd_dir2(data, temp, original_path, *i);
			if (g_last_exit_status == 1)
				break ;
		}
		else
		{
			err_no_such_file();
			break ;
		}
		(*i)++;
	}
}

void	cmd_cd_dir(t_data *data)
{
	char	*original_path;
	char	**temp;
	int		i;

	if (!data->current_path)
	{
		err_no_such_file();
		return ;
	}
	original_path = ft_strdup(data->current_path);
	temp = ft_split(data->cmd_list->args[1], '/');
	i = 0;
	cd_dir_loop(data, temp, &original_path, &i);
	update_path(data, original_path, temp, i);
}
