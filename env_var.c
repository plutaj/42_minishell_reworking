/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:07:32 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/29 18:14:44 by jozefpluta       ###   ########.fr       */
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