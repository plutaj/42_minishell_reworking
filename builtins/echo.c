/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:19:40 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/17 15:29:23 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_echo(t_command *cmd_list)
{
    if (ft_strcmp(cmd_list->args[1], "-n") == 0)
        cmd_echo_exec(cmd_list, 0);
    else if (cmd_list)
        cmd_echo_exec(cmd_list, 1);
}

void	cmd_echo_exec(t_command *cmd_list, int is_newline)
{
	char	*str;

	str = convert_to_string(cmd_list, is_newline);
	// case with -n
	if (!is_newline)
		printf("%s", str);
	else
		printf("%s\n", str);
}

char	*convert_to_string(t_command *cmd_list, int is_newline)
{
	char	*orig_str;
	char	*temp;
	int		i;

	orig_str = NULL;
	temp = NULL;
	if (is_newline)
		i = 2;
	else
		i = 1;
	while (cmd_list->args[i])
	{
		if (dollar_sign(cmd_list->args[i]))
			put_variable(i, cmd_list, &orig_str);
		else if (orig_str == NULL)
			orig_str = ft_strdup(cmd_list->args[i]);
		else
		{
			temp = ft_strjoin(orig_str, " ");
			free(orig_str);
			orig_str = ft_strjoin(orig_str, cmd_list->args[i]);
			free(temp);
		}
		i++;
	}
	return (orig_str);
}

void	put_variable(int i, t_command *cmd_list, char **orig_str)
{
	char	*temp;
	char	*str;

	temp = NULL;
	str = NULL;
	if ((str = is_env_var(cmd_list->args[i], cmd_list->data->env)) != NULL) // ! add to compare not only agains a env vars but also agains own variables
	{
		if (!*orig_str)
			*orig_str = ft_strdup(str);
		else
		{
			temp = ft_strjoin(*orig_str, " ");
			free(*orig_str);
			*orig_str = ft_strjoin(temp, str);
			free(temp);
		}
	}
	// else if ()
	// {
		// case of own variables
	// }
	// else
		// case that no var found after $
}

int	dollar_sign(char *str)
{
	if (*str == '$')
		return (1);
	return (0);
}