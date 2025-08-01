/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:30:16 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/01 16:36:52 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_cd_dir2(t_data *data, char **temp, char **original_path, int i)
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

int	list_directory_contents(char *str, const char *path)
{
	struct dirent	*entry;
	DIR				*dp;

	dp = opendir(path);
	if (dp == NULL)
	{
		perror("opendir");
		exit(1);
	}
	entry = readdir(dp);
	while (entry != NULL)
	{
		if (ft_strcmp(str, entry->d_name) == 0)
		{
			closedir(dp);
			return (1);
		}
		entry = readdir(dp);
	}
	closedir(dp);
	return (0);
}
