/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:08:56 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/09 16:06:00 by huahmad          ###   ########.fr       */
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
		find_variables(new_cmd);
		if (!data->cmd_list)
			data->cmd_list = new_cmd;
		else
			temp_cmd->next = new_cmd;
		temp_cmd = new_cmd;
		i++;
	}
	free_2d_array(s);
}

t_command *split_args_and_redirs(t_command *new_cmd, char *s)
{
	char **args = calloc(256, sizeof(char *));
	int i = 0, j = 0;
	char quote = 0;
	char buffer[1024];
	int buf_i = 0;

	while (s[i])
	{
		// Skip spaces outside quotes
		if (!quote && s[i] == ' ')
		{
			if (buf_i > 0)
			{
				buffer[buf_i] = '\0';
				args[j++] = ft_strdup(buffer);
				buf_i = 0;
			}
			i++;
			continue;
		}

		// Start or end a quote block
		if ((s[i] == '\'' || s[i] == '\"'))
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
			else
				buffer[buf_i++] = s[i]; // mismatched quote, keep it
			i++;
			continue;
		}

		// Add char to buffer
		buffer[buf_i++] = s[i++];
	}
	if (buf_i > 0)
	{
		buffer[buf_i] = '\0';
		args[j++] = ft_strdup(buffer);
	}

	args[j] = NULL;
	new_cmd->args = args;
	return new_cmd;
}


// t_command	*split_args_and_redirs(t_command *new_cmd, char *s)
// {
// 	char	**new_s;
// 	int		i;
// 	int		arg_i;
// 	char	quote;
// 	char	*temp;
// 	char	*arg;

	// new_s = ft_split(s, ' ');
	// i = 0;
	// arg_i = 0;
	// quote = 0;
	// new_cmd->args = (char **)calloc(254, sizeof(char *));
	// while (new_s[i])
	// {
	// 	if (starts_with_quote(new_s[i]))
	// 	{
	// 		quote = new_s[i][0];
	// 		arg = ft_strdup(new_s[i]);
			// i++;

			// while (new_s[i] && !ends_with_quote(new_s[i], quote))
			// {
			// 	temp = ft_strjoin(arg, " ");
			// 	free(arg);
			// 	arg = temp;

			// 	temp = ft_strjoin(arg, new_s[i]);
			// 	free(arg);
			// 	arg = temp;
			// 	i++;
			// }
			// if (new_s[i] && ends_with_quote(new_s[i], quote))
			// {
			// 	temp = ft_strjoin(arg, " ");
			// 	free(arg);
			// 	arg = temp;

			// 	temp = ft_strjoin(arg, new_s[i]);
// 				free(arg);
// 				arg = temp;
// 				i++;
// 			}
// 			new_cmd->args[arg_i++] = arg;
// 		}
// 		else
// 		{
// 			new_cmd->args[arg_i++] = ft_strdup(new_s[i]);
// 			i++;
// 		}
// 	}
// 	new_cmd->args[arg_i] = NULL;
// 	free_2d_array(new_s);
// 	return (new_cmd);
// }

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
