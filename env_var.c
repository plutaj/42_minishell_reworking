/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:07:32 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/17 15:08:43 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy_envp(char **envp)
{
    int i = 0;
    int count = 0;
    char **env;

    // Count how many environment variables there are
    while (envp[count])
        count++;
    // Allocate memory for your own environment array (+1 for NULL terminator)
    env = malloc(sizeof(char *) * (count + 1));
    if (!env)
    {
        perror("malloc");
        return NULL;
    }

    // Copy each string
    while (i < count)
    {
        env[i] = ft_strdup(envp[i]);
        if (!env[i])
        {
            perror("strdup");
            // Free everything if one strdup fails
            while (--i >= 0)
                free(env[i]);
            free(env);
            return NULL;
        }
        i++;
    }
    env[i] = NULL; // NULL-terminate the array
    return env;
}

// Function to extract the value of an environment variable from the input
char	*is_env_var(char *input, char **envp)
{
    char env_var[256];
    int i;
    char *result;

    i = 0;
    result = NULL;
    input++; // skip '$' sign
    strncpy_until_char(env_var, input, '=');
    while (envp[i])
	{
        if (ft_strncmp(env_var, envp[i], ft_strlen(env_var)) == 0)
		{
            result = ft_strchr(envp[i], '=');
            if (result)
			{
                result++; // skip '=' sign
                return (result);
            }
        }
        i++;
    }
    return (NULL);
}

// Function to copy characters until a specific character is found
void strncpy_until_char(char *dest, const char *src, char stop_char)
{
    while (*src != '\0' && *src != stop_char)
	{
        *dest = *src;
        dest++; 
        src++;
    }
    *dest = '\0';
}