/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:08:56 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/09 15:59:38 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (ends_with_quote(new_s[i], quote))
			{
				// Just a single quoted token, keep quotes
				new_cmd->args[arg_i++] = ft_strdup(new_s[i]);
				i++;
				continue ;
			}
			// Start of a multi-token quoted string
			arg = ft_strdup(new_s[i]); // keep the starting quote
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
				temp = ft_strjoin(arg, " ");
				free(arg);
				arg = temp;
				temp = ft_strjoin(arg, new_s[i]); // keep the ending quote
				free(arg);
				arg = temp;
				i++;
			}
			new_cmd->args[arg_i++] = arg;
		}
		else
		{
			new_cmd->args[arg_i++] = ft_strdup(new_s[i]);
			i++;
		}
	}
	new_cmd->args[arg_i] = NULL;
	free_2d_array(new_s);
	return (new_cmd);
}

// t_command	*split_args_and_redirs(t_command *new_cmd, char *s)
// {
// 	char	**new_s;
// 	int		i;
// 	int		arg_i;
// 	char	quote;
// 	char	*temp;
// 	char	*arg;

// 	new_s = ft_split(s, ' ');
// 	i = 0;
// 	arg_i = 0;
// 	quote = 0;
// 	new_cmd->args = (char **)calloc(254, sizeof(char *));
// 	while (new_s[i])
// 	{
// 		if (starts_with_quote(new_s[i]))
// 		{
// 			quote = new_s[i][0];
// 			// added
// 			if (ends_with_quote(new_s[i], quote) && ft_strlen(new_s[i]) > 1)
// 			{
// 				// Quote starts and ends in same token — remove both quotes
// 				char *trimmed = ft_substr(new_s[i], 1, ft_strlen(new_s[i]) - 2);
// 				new_cmd->args[arg_i++] = trimmed;
// 				i++;
// 				continue ;
// 			}
// 			// added
// 			arg = ft_strdup(new_s[i] + 1); // skip the opening quote
// 			i++;
// 			while (new_s[i] && !ends_with_quote(new_s[i], quote))
// 			{
// 				temp = ft_strjoin(arg, " ");
// 				free(arg);
// 				arg = temp;
// 				temp = ft_strjoin(arg, new_s[i]);
// 				free(arg);
// 				arg = temp;
// 				i++;
// 			}
// 			if (new_s[i] && ends_with_quote(new_s[i], quote))
// 			{
// 				new_s[i][ft_strlen(new_s[i]) - 1] = '\0';
// 				temp = ft_strjoin(arg, " ");
// 				free(arg);
// 				arg = temp;
// 				temp = ft_strjoin(arg, new_s[i]);
// 				free(arg);
// 				arg = temp;
// 				i++;
// 			}
// 			new_cmd->args[arg_i++] = arg;
// 		}
// 		else
// 		{
// 			new_cmd->args[arg_i++] = ft_strdup(new_s[i]);
// 			i++; // added this 
// 		}
// 		// i++; // commented this
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