/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:04:27 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/09 16:49:15 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* printing purposes */
void	print_linked_list(t_command *commands)
{	
	int		i;
	t_redir *redir;

	i = 0;
	if (commands->args[i])
	{
		printf("\nArray of commands:");
		while (commands->args[i])
			printf("\n%s", commands->args[i++]);
	}
	printf("\n");
	if (commands->redir != NULL)
		printf("\nList of redirections:");
	redir = commands->redir;
	while (redir)
	{
		printf("\nTYPE %u\nFILE OR DELIMITER: %s", redir->type, redir->file_or_limiter);
		redir = redir->next;
	}
	printf("\n");
	printf("\n");
	i = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void)argc;
	(void)argv;
	if (argc != 1)
		return (printf("Error: Unexpected input.\n"));
	init_data(&data, envp);
	while (1)
	{
		data.input = readline("minishell$ ");
		if (data.input)
			add_history(data.input);
		if (!(check_for_quotes(&data)))
		{
			printf("Wrong number of quotes\n");
			exit(1); // handle this like not correct pair of quotes
		}
		create_command_list(&data);
		create_redir_list(&data);
		print_linked_list(data.commands);
		set_data_to_default(&data);
	}
    return (0);
}