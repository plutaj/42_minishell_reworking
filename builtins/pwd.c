/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:57:01 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/01 16:40:50 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_pwd(t_data *data)
{
	if (data->current_path)
		free (data->current_path);
	get_path(data);
	printf("%s\n", data->current_path);
	g_last_exit_status = 0;
}
