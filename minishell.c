/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:04:27 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/07 15:59:34 by jozefpluta       ###   ########.fr       */
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
				printf("%d ARGS: ", node);
		while (cmd_list->args[i])
		{
			printf("\n|%s|", cmd_list->args[i]);
			i++;
		}
		printf("\n_______________________________________");
		if (cmd_list->redir)
			printf("%d REDIRS: ", node);
		while (cmd_list->redir)
		{
			printf("TYPE %u %s", cmd_list->redir->type, cmd_list->redir->file_or_limiter);
			cmd_list->redir = cmd_list->redir->next;
		}
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
	char		*new_args;
	int			i;
	
	cmd_list = data->cmd_list;
	i = 0;
	new_args = (char **)malloc(sizeof(char *) * 254);
	while (cmd_list)
	{
		while (cmd_list->args)
		{
			if (check_for_redir(cmd_list->args[i]));
			{
				// funkcia ktora CUTne aktualny args o "i" rows a vytvori z nich linked list of redirections
				if (cmd_list->args[i + 1])
				{
					cmd_list->redir = add_redir_node(cmd_list->args[i], cmd_list->args[i + 1]);
					// funkcia ktora CUTne aktualny args o "i" rowS
				}
			}
			i++;
		}
		cmd_list = cmd_list->next;
	}
}

t_redir	*add_redir_node(char *token, char *file_or_delimiter)
{
	t_redir *new;

	
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
			}
			new_cmd->args[arg_i++] = arg;
		}
		else
			new_cmd->args[arg_i++] = ft_strdup(new_s[i]);
		i++;
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