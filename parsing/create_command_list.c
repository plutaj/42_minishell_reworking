/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:08:56 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/03 11:00:05 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_command_list(t_data *data)
{
	char		**s;
	int			i;
	t_command	*new_cmd;
	t_command	*temp_cmd;

	s = ft_split_quote_aware(data->input, '|');
	i = 0;
	while (s[i])
	{
		new_cmd = (t_command *)malloc(sizeof(t_command));
		new_cmd->args = NULL;
		new_cmd->redir = NULL;
		new_cmd->data = data;
		new_cmd->next = NULL;
		new_cmd = split_args_and_redirs(new_cmd, s[i]);
		// print_linked_list(data->cmd_list); // there
		find_variables(new_cmd);
		remove_quotes_from_args(new_cmd->args);
		if (!data->cmd_list)
			data->cmd_list = new_cmd;
		else
			temp_cmd->next = new_cmd;
		temp_cmd = new_cmd;
		i++;
	}
	free_2d_array(s);
}

// t_command *split_args_and_redirs(t_command *new_cmd, char *s)
// {
// 	char **args = calloc(256, sizeof(char *));
// 	int i = 0, j = 0;
// 	char buffer[1024];
// 	int buf_i = 0;
// 	char quote = 0;

// 	while (s[i])
// 	{
// 		// Skip spaces outside quotes
// 		if (!quote && s[i] == ' ')
// 		{
// 			if (buf_i > 0)
// 			{
// 				buffer[buf_i] = '\0';
// 				args[j++] = ft_strdup(buffer);
// 				buf_i = 0;
// 			}
// 			i++;
// 			continue;
// 		}

// 		// Toggle quote state (but still copy quotes)
// 		if (s[i] == '\'' || s[i] == '\"')
// 		{
// 			if (!quote)
// 				quote = s[i];
// 			else if (quote == s[i])
// 				quote = 0;
// 		}

// 		// Add character (including quotes) to buffer
// 		buffer[buf_i++] = s[i++];
// 	}

// 	// Handle last token
// 	if (buf_i > 0)
// 	{
// 		buffer[buf_i] = '\0';
// 		args[j++] = ft_strdup(buffer);
// 	}

// 	args[j] = NULL;
// 	new_cmd->args = args;
// 	return new_cmd;
// }

// int	handle_spaces(char *s, int *i, char **args, int *j, char *buffer, int *buf_i)
// {
// 	if (s[*i] == ' ')
// 	{
// 		if (*buf_i > 0)
// 		{
// 			buffer[*buf_i] = '\0';
// 			args[(*j)++] = ft_strdup(buffer);
// 			*buf_i = 0;
// 		}
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }

// int	handle_redirections(char *s, int *i, char **args, int *j, char *buffer, int *buf_i)
// {
// 	if (s[*i] == '<' || s[*i] == '>')
// 	{
// 		if(*buf_i > 0)
// 		{
// 			buffer[*buf_i] = '\0';
// 			args[(*j)++] = ft_strdup(buffer);
// 			*buf_i = 0;
// 		}
// 		if ((s[*i] == '<' && s[*i + 1] == '<') || (s[*i] == '>' && s[*i + 1] == '>'))
// 		{
// 			buffer[0] = s[*i];
// 			buffer[1] = s[*i + 1];
// 			buffer[2] = '\0';
// 			args[(*j)++] = ft_strdup(buffer);
// 			(*i)++;
// 		}
// 		else
// 		{
// 			buffer[0] = s[*i];
// 			buffer[1] = '\0';
// 			args[(*j)++] = ft_strdup(buffer);
// 			(*i)++;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// void	handle_quotes(char c, char *quote)
// {
// 	if (c =='\'' || c == '\"')
// 	{
// 		if (!(*quote))
// 			*quote = c;
// 		else if (*quote == c)
// 			*quote = 0; 
// 	}
// }

// t_command *split_args_and_redirs(t_command *new_cmd, char *s)
// {
// 	char	**args;
// 	int		i;
// 	int		j;
// 	char	buffer[1024];
// 	int		buf_i;
// 	char	quote;

// 	args = ft_calloc(256, sizeof(char *));
// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		handle_quotes(s[i], &quote);
// 		if (!quote && handle_redirections(s, &i, args, &j, buffer, &buf_i))
// 			continue;
// 		if (!quote && handle_spaces(s, &i, args, &j, buffer, &buf_i))
// 			continue;
// 		printf("buffer %s\n s %s \n", buffer, s);
// 		buffer[buf_i++] = s[i++];
// 	}
// 	if (buf_i > 0)
// 	{
// 		buffer[buf_i] = '\0';
// 		args[j++] = ft_strdup(buffer);
// 	}
// 	args[j] = NULL;
// 	new_cmd->args = args;
// 	return (new_cmd);
// }

char *remove_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	result = malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	quote = 0;
	if (!result)
		return NULL;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (!quote)
			{
				quote = str[i];  // Enter quote context
				i++;
				continue;        // Skip opening quote
			}
			else if (quote == str[i])
			{
				quote = 0;       // Exit quote context
				i++;
				continue;        // Skip closing quote
			}
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	remove_quotes_from_args(char **args)
{
	int		i = 0;
	char	*cleaned;

	while (args[i])
	{
		cleaned = remove_quotes(args[i]);
		free(args[i]);
		args[i] = cleaned;
		i++;
	}
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
