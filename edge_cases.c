/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:10:39 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/29 18:11:30 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void	edge_case(t_data *data)
{
	if (!check_for_quotes(data))
	{
		printf("quote>\n");
		set_data_to_default(data);
		return ;
	}
}

int	check_for_quotes(t_data *data)
{
	const char	*line;
	int			single_quotes;	
	int			double_quotes;	
	
	line = data->input;
	single_quotes = 0;
	double_quotes = 0;
	while (*line)
	{
		if (*line == '\'')
			single_quotes++;
		if (*line == '\"')
			double_quotes++;
		line++;
	}
	if (single_quotes % 2 == 1 || double_quotes % 2 == 1)
		return (0);
	return (1);
}