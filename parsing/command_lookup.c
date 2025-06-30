/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:08:59 by huahmad           #+#    #+#             */
/*   Updated: 2025/06/30 20:11:29 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *search_in_paths(char **splited_path, char *cmd)
{
    int i = 0;
    char *path;

    while (splited_path[i])
    {
        path = concatenate_paths(splited_path[i], cmd);
        if (!path)
            return (NULL);
        if (access(path, X_OK) == 0)
        {
            free_2d_array(splited_path);
            return (path);
        }
        free(path);
        i++;
    }
    free_2d_array(splited_path);
    return (NULL);
}

char *find_command_in_path(char *cmd)
{
    char *path_env;
    char *path;
    char **splited_path;

    path_env = getenv("PATH");
    path = ft_strdup(path_env);
    if (!path)
        return (NULL);
    splited_path = ft_split(path, ':');
    free(path);
    return search_in_paths(splited_path, cmd);
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
