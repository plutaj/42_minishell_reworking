/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:06:06 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/29 14:05:43 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
