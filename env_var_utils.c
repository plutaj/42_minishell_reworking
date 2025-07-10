/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:43:10 by huahmad           #+#    #+#             */
/*   Updated: 2025/07/10 13:43:18 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

