/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:13:10 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/14 15:58:19 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linked_list(t_command *cmd_list)
{
	int	i;
	int	node;

	i = 0;
	node = 0;
	while (cmd_list)
	{
		if (cmd_list->args[i])
				printf("NODE %d \nArray of commands:", node);
		while (cmd_list->args[i])
		{
			printf("\n|%s|", cmd_list->args[i]);
			i++;
		}
		printf("\n");
		if (cmd_list->redir != NULL)
			printf("\nList of redirections:");
		if (!cmd_list->redir)
        	fprintf(stderr, "data->cmd_list->redir is NULL\n");
		while (cmd_list->redir)
		{
			printf("\nTYPE %u\n%s", cmd_list->redir->type,
				cmd_list->redir->file_or_limiter);
			cmd_list->redir = cmd_list->redir->next;
		}

		printf("\n");
		printf("\n");
		i = 0;
		node++;
		cmd_list = cmd_list->next;
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	if (argc != 1)
		return (printf("Error: Unexpected input.\n"));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	init_data(&data, envp);
	while (1)
	{
		data.input = readline("\033[32mminishell$ \033[0m");
		if (data.input == NULL)
		{
			printf("exit\n");
			set_data_to_default(&data);
			exit(0);
		}
		if (!*data.input || only_spaces(data.input))
			continue ;
		if (*data.input)
			add_history(data.input);
		if (!(check_for_quotes(&data)))
		{
			printf("Wrong number of quotes\n");
			exit(1); // handle this like not correct pair of quotes
		}
		create_command_list(&data);
		create_redir_list(&data);
		// print_linked_list(data.cmd_list);
		execution(&data);
		set_data_to_default(&data);
	}
	return (0);
}

