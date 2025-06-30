/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:46:18 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/29 15:28:39 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_quotes(t_data *data)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	if (data == NULL || data->input == NULL)
		return (1);
	while (data->input[i])
	{
		if (data->input[i] == '\'' && !in_single && !in_double)
			in_single = 1;
		else if (data->input[i] == '\"' && !in_double && !in_single)
			in_double = 1;
		else if (data->input[i] == '\'' && in_single && !in_double)
			in_single = 0;
		else if (data->input[i] == '\"' && in_double && !in_single)
			in_double = 0;
		i++;
	}
	if (in_single || in_double)
		return (0);
	return (1);
}
