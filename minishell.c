/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:04:27 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/30 16:28:41 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* printing purposes */
void	print_linked_list(t_command *cmd_list)
{	
	int	i;
	int node;

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
		while (cmd_list->redir)
		{
			printf("\nTYPE %u\n%s", cmd_list->redir->type, cmd_list->redir->file_or_limiter);
			cmd_list->redir = cmd_list->redir->next;
		}
		printf("\n");
		printf("\n");
		i = 0;
		node++;
		cmd_list = cmd_list->next;
	}
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
		data.input = readline("\033[32mminishell$ \033[0m");
		if (data.input == NULL) {
			printf("error here\n");
			exit(0);
		}
		if (!*data.input || only_spaces(data.input)) // edited
			continue ; // edited
		if (*data.input )
			add_history(data.input); //edited
		if (!(check_for_quotes(&data)))
		{
			printf("Wrong number of quotes\n");
			exit(1); // handle this like not correct pair of quotes
		}
		create_command_list(&data);
		create_redir_list(&data);
		execution(&data);
		set_data_to_default(&data);
	}
    return (0);
}

int	only_spaces(const char *s)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (*str == ' ')
			str++;
		else
			return(0);
	}
	return (1);
}
