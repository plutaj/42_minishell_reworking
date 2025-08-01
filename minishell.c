/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:13:10 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/08/01 16:40:54 by huahmad          ###   ########.fr       */
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
	free_env(data.env);
	return (0);
}

void	delete_later(t_data *data)
{
	t_command	*cmd;
	int			cmd_num;
	t_redir		*redir;

	cmd = data->cmd_list;
	cmd_num = 0;
	while (cmd)
	{
		printf("command %d:\n", cmd_num++);
		if (cmd->args)
		{
			for (int i = 0; cmd->args[i]; i++)
				printf("  args[%d]: '%s'\n", i, cmd->args[i]);
		}
		else
			printf("  (no args)\n");
		redir = cmd->redir;
		while (redir)
		{
			printf("  the redir: type=%d, file_or_limiter='%s'\n", redir->type,
				redir->file_or_limiter);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
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
		// delete_later(data);
		if (!check_syntax(data))
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
