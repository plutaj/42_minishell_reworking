/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:13:10 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/19 21:56:42 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (argc != 1)
		return (printf("Error: Unexpected input.\n"));
	signal(SIGINT, sigint_handler);
	init_data(&data, envp);
	if (!data.env)
		return (1);
	minishell_loop(&data);
	return (0);
}

void	minishell_loop(t_data *data)
{
	while (1)
	{
		data->input = readline(GREEN "minishell$ " RESET);
		if (data->input == NULL)
			readline_failure(data);
		if (!*data->input || only_spaces(data->input))
			continue ;
		if (!valid_input(data->input))
			continue ;
		if (*data->input)
			add_history(data->input);
		if (!quotes_no_pair(data))
			continue ;
		create_command_list(data);
		if (!data->cmd_list)
			cleanup_and_exit(data);
		create_redir_list(data);
		if (!check_syntax(data)) // syntax protec
		{
			set_data_to_default(data);
			continue ;
		}
		execution(data);
		set_data_to_default(data);
	}
}

int	readline_failure(t_data *data)
{
	printf("exit\n");
	if (*data->current_path)
		free(data->current_path);
	free_2d_array(data->env);
	set_data_to_default(data);
	exit(0);
}

int	quotes_no_pair(t_data *data)
{
	if (!check_for_quotes(data))
	{
		printf("Wrong number of quotes\n");
		set_data_to_default(data);
		return (0);
	}
	return (1);
}
