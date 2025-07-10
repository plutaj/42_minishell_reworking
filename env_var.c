/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:07:32 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/10 22:40:34 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_dup_err(char **env, int i)
{
	perror("strdup");
	while (--i >= 0)
		free(env[i]);
	free(env);
}

char	**copy_envp(char **envp)
{
	int		i;
	int		count;
	char	**env;

	i = 0;
	count = 0;
	while (envp[count])
		count++;
	env = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			str_dup_err(env, i);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	update_env_var(char **envp, const char *key, const char *value)
{
	int		i;
	char	*new_entry;

	i = 0;
	while (envp[i])
	{
		if (update_existing_env(envp, i, key, value))
			return (1);
		else if (ft_strcmp(envp[i], key) == 0)
		{
			free(envp[i]);
			if (ft_strlen(value) > 0)
				new_entry = ft_strjoin3(key, "=", value);
			else
				new_entry = ft_strjoin3(key, "", value);
			if (!new_entry)
				return (0);
			envp[i] = new_entry;
			return (1);
		}
		i++;
	}
	return (0);
}

int	update_existing_env(char **envp, int i,
	const char *key, const char *value)
{
	int		key_len;
	int		current_key_len;
	char	*equal_sign;
	char	*new_entry;

	equal_sign = ft_strchr(envp[i], '=');
	if (!equal_sign)
		return (0);
	key_len = ft_strlen(key);
	current_key_len = equal_sign - envp[i];
	if (current_key_len == key_len && ft_strncmp(envp[i], key, key_len) == 0)
	{
		free(envp[i]);
		new_entry = ft_strjoin3(key, "=", value);
		if (!new_entry)
			return (0);
		envp[i] = new_entry;
		return (1);
	}
	return (0);
}

char	*is_env_var(char *arg, char **envp)
{
	int		i;
	char	*key;
	char	*env_entry;
	char	*equal_sign;
	int		name_len;

	i = 0;
	key = arg + 1;
	while (envp[i])
	{
		env_entry = envp[i];
		equal_sign = ft_strchr(env_entry, '=');
		if (equal_sign)
		{
			name_len = equal_sign - env_entry;
			if ((int)ft_strlen(key) == name_len
				&& ft_strncmp(env_entry, key, (int)ft_strlen(key)) == 0)
				return (equal_sign + 1);
		}
		i++;
	}
	return (NULL);
}
