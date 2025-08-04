/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:43:10 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/04 19:09:40 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	strncpy_until_char(char *dest, const char *src, char stop_char)
{
	while (*src != '\0' && *src != stop_char)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

int	env_var_exists(char *key, char **envp)
{
	int		i;
	int		j;

	i = 0;
	if (!key || !envp)
		return (0);
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=' && key[j])
		{
			if (envp[i][j] != key[j])
				break ;
			j++;
		}
		if (envp[i][j] == '=' && key[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	if (!env_var_exists("PATH", env))
	{
		g_last_exit_status = 127;
		printf("minishell$: env: No such file or directory\n");
		return ;
	}
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
