/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:07:32 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/08 11:04:39 by jozefpluta       ###   ########.fr       */
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

int	update_env_var(char **envp, const char *key, const char *value)
{
	int     i;
	int     key_len;
	char    *new_entry;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			free(envp[i]); // free old "KEY=VALUE"
			new_entry = ft_strjoin3(key, "=", value); // custom function to join 3 strings
			envp[i] = new_entry;
			return (1);
		}
		i++;
	}
    return (0);
}

// Function to extract the value of an environment variable from the input
char *is_env_var(char *arg, char **envp)
{
    int     i;
    char    *key;
    int     key_len;
    char    *env_entry;
    char    *equal_sign;
    int     name_len;

    i = 0;
    key = arg + 1;
    key_len = ft_strlen(key);
    while (envp[i])
    {
        env_entry = envp[i];
        equal_sign = ft_strchr(env_entry, '=');
        if (equal_sign)
        {
            name_len = equal_sign - env_entry;
            if (key_len == name_len && ft_strncmp(env_entry, key, key_len) == 0)
                return (equal_sign + 1); // value part after '='
        }
        i++;
    }
    return (NULL);
}
// char	*is_env_var(char *input, char **envp)
// {
//     char env_var[256];
//     int i;
//     char *result;

//     i = 0;
//     result = NULL;
//     input++; // skip '$' sign
//     strncpy_until_char(env_var, input, '=');
//     while (envp[i])
// 	{
//         if (ft_strncmp(env_var, envp[i], ft_strlen(env_var)) == 0)
// 		{
//             result = ft_strchr(envp[i], '=');
//             if (result)
// 			{
//                 result++; // skip '=' sign
//                 return (result);
//             }
//         }
//         i++;
//     }
//     return (NULL);
// }

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

void    print_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}