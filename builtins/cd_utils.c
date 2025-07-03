/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:06:06 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/03 17:28:04 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_path(t_data *data, char *original_path, char **temp)
{
	if (data->current_path)
		free(data->current_path);
	data->current_path = original_path;
	update_env_var(data->env, "PWD", original_path);
	free_2d_array(temp);
}

void	update_path_failed(char **temp, char *original_path)
{
	free_2d_array(temp);
	free (original_path);
}

void	err_no_such_file(void)
{
	write(STDERR_FILENO, " No such file or directory\n", 28);
	g_last_exit_status = 1;
}

int	count_slash(char *str)
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

char	*append_char_to_str(char *str, char c)
{
	size_t	len;
	char	*new_str;

	if (!str)
	{
		new_str = malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
