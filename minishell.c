/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:04:27 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/08 18:01:37 by jpluta           ###   ########.fr       */
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
			printf("\n%s", cmd_list->args[i]);
			i++;
		}
		printf("\n");
		if (cmd_list->redir != NULL)
			printf("\nList of redirections:");
		while (cmd_list->redir)
		{
			printf("\nTYPE %u\n FILE OR DELIMITER%s", cmd_list->redir->type, cmd_list->redir->file_or_limiter);
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
		print_linked_list(data.cmd_list);
		set_data_to_default(&data);
	}
    return (0);
}

int	check_for_redir(char *arg)
{
	if (ft_strcmp(arg, "<") == 0)
		return (1);
	else if (ft_strcmp(arg, ">") == 0)
		return (1);
	else if (ft_strcmp(arg, "<<") == 0)
		return (1);
	else if (ft_strcmp(arg, ">>") == 0)
		return (1);
	return (0);
}


void	create_redir_list(t_data *data)
{
	t_command	*cmd_list;
	int			i;
	int			x;
	
	cmd_list = data->cmd_list;
	i = 0;
	while (cmd_list)
	{
		while (cmd_list->args && cmd_list->args[i])
		{
			if (check_for_redir(cmd_list->args[i]))
			{
				add_redir_node(&(cmd_list->args[i]), cmd_list);
				x = i;
				while (cmd_list->args[x])
					free(cmd_list->args[x++]);
				cmd_list->args[i] = NULL;
				continue ;
			}
			i++;
		}
		i = 0;
		cmd_list = cmd_list->next;
	}
}

void	add_redir_node(char **args, t_command *cmd_list)
{
	t_redir *new_redir;
	t_redir *temp_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (ft_strcmp(args[0], "<") == 0)
		new_redir->type = REDIR_INPUT;
	else if (ft_strcmp(args[0], ">") == 0)
		new_redir->type = REDIR_OUTPUT;
	else if (ft_strcmp(args[0], ">>") == 0)
		new_redir->type = REDIR_APPEND;
	else if (ft_strcmp(args[0], "<<") == 0)
		new_redir->type = REDIR_HEREDOC;
	if (args[1])
		new_redir->file_or_limiter = ft_strdup(args[1]);
	else
		new_redir->file_or_limiter = NULL;
	new_redir->next = NULL;
	if (!cmd_list->redir)
		cmd_list->redir = new_redir;
	else
	{
		temp_redir = cmd_list->redir;
		while (temp_redir)
			temp_redir = temp_redir->next;
		temp_redir = new_redir;
		temp_redir->next = NULL;
	}
}

void	create_command_list(t_data *data)
{
	char		**s;
	int			i;
	t_command	*new_cmd;
	t_command	*temp_cmd;

	s = ft_split(data->input, '|');
	i = 0;
	while (s[i])
	{
		new_cmd = (t_command *)malloc(sizeof(t_command));
		new_cmd->args = NULL;
		new_cmd->redir = NULL;
		new_cmd->next = NULL;
		new_cmd = split_args_and_redirs(new_cmd, s[i]);
		if (!data->cmd_list)
			data->cmd_list = new_cmd;
		else
			temp_cmd->next = new_cmd;
		temp_cmd = new_cmd;
		i++;
	}
	free_2d_array(s);
}

t_command	*split_args_and_redirs(t_command *new_cmd, char *s)
{
	char	**new_s;
	int		i;
	int		arg_i;
	char	quote;
	char	*temp;
	char	*arg;

	new_s = ft_split(s, ' ');
	i = 0;
	arg_i = 0;
	quote = 0;
	new_cmd->args = (char **)calloc(254, sizeof(char *));
	while (new_s[i])
	{
		if (starts_with_quote(new_s[i]))
		{
			quote = new_s[i][0];
			// added
			if (ends_with_quote(new_s[i], quote) && ft_strlen(new_s[i]) > 1)
			{
				// Quote starts and ends in same token — remove both quotes
				char *trimmed = ft_substr(new_s[i], 1, ft_strlen(new_s[i]) - 2);
				new_cmd->args[arg_i++] = trimmed;
				i++;
				continue ;
			}
			// added
			arg = ft_strdup(new_s[i] + 1); // skip the opening quote
			i++;
			while (new_s[i] && !ends_with_quote(new_s[i], quote))
			{
				temp = ft_strjoin(arg, " ");
				free(arg);
				arg = temp;
				temp = ft_strjoin(arg, new_s[i]);
				free(arg);
				arg = temp;
				i++;
			}
			if (new_s[i] && ends_with_quote(new_s[i], quote))
			{
				new_s[i][ft_strlen(new_s[i]) - 1] = '\0';
				temp = ft_strjoin(arg, " ");
				free(arg);
				arg = temp;
				temp = ft_strjoin(arg, new_s[i]);
				free(arg);
				arg = temp;
				i++;
			}
			new_cmd->args[arg_i++] = arg;
		}
		else
		{
			new_cmd->args[arg_i++] = ft_strdup(new_s[i]);
			i++; // added this 
		}
		// i++; // commented this
	}
	new_cmd->args[arg_i] = NULL;
	free_2d_array(new_s);
	return (new_cmd);
}

int starts_with_quote(const char *s)
{
	return (s[0] == '\'' || s[0] == '\"');
}

int ends_with_quote(const char *s, char quote)
{
	int len = ft_strlen(s);
	if (len == 0)
		return 0;
	return (s[len - 1] == quote);
}

int	get_index_of_quotes(char *s, t_data *data)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			data->is_single = 1;
			return (i);
		}
		else if (s[i] == '\"')
		{
			data->is_double = 1;
			return (i);
		}
		i++;
	}
	return (0);
}