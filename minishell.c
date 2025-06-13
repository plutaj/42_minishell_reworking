/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:13:10 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/06/13 18:20:06 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_last_exit_status;
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
		if (!cmd_list->redir)
    	{
        	fprintf(stderr, "data->cmd_list->redir is NULL\n");
        	// return -1;
    	}
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
	g_last_exit_status = 0;
	if (argc != 1)
		return (printf("Error: Unexpected input.\n"));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	init_data(&data, envp);
	while (1)
	{
		data.input = readline("\033[32mminishell$ \033[0m");
		if (data.input == NULL) {
			printf("exit\n");
			set_data_to_default(&data);
			exit(0);
		}
		if (!*data.input || only_spaces(data.input)) 
			continue ; 
		if (*data.input )
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

void sigint_handler(int signo)
{
    // Write newline and redisplay prompt
    // This prevents readline from breaking the shell
	(void)signo;
    write(1, "\n", 1);
    rl_on_new_line();  // Tell readline a new line is starting
    rl_replace_line("", 0);  // Clear the current input line
    rl_redisplay();  // Redisplay prompt
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

// sort < fruits.txt