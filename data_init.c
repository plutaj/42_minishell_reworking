/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:22:09 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/29 18:22:31 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->env = copy_envp(envp); // set a env var 2d array
	data->input = NULL;
	get_path(data); // set a current path in data struct
	data->cmd_list = NULL;
	data->redir_list = NULL;
}

void	get_path(t_data *data)
{
	char	*cwd;
    char	buffer[1024];

    cwd = getcwd(buffer, sizeof(buffer));
    if (cwd == NULL)
	{
		perror("getcwd() error");
		exit(1);
	}
	data->current_path = ft_strdup(cwd);
}