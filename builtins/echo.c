/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:19:40 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/31 14:40:44 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_echo(t_command *cmd_list)
{
    if (ft_strcmp(cmd_list->args[1], "-n") == 0)
        cmd_echo_exec(cmd_list, 0);
    else
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
	char	*with_space;
	int		i;

	orig_str = NULL;
	temp = NULL;
	with_space = NULL;
	if (is_newline)
		i = 1;
	else
		i = 2;
	while (cmd_list->args[i])
	{
		if (dollar_sign(cmd_list->args[i]))
			put_variable(i, cmd_list, &orig_str);
		else if (orig_str == NULL)
			orig_str = ft_strdup(cmd_list->args[i]);
		else
		{
			with_space = ft_strjoin(orig_str, " ");
			free(orig_str);
			temp = ft_strjoin(with_space, cmd_list->args[i]);
			free(with_space);
			orig_str = temp;
		}
		i++;
	}
	return (orig_str);
}

void	put_variable(int i, t_command *cmd_list, char **orig_str)
{
	char	*temp;
	char	*str;
	char	*with_space;

	temp = NULL;
	str = NULL;
	with_space = NULL;
	if ((str = is_env_var(cmd_list->args[i], cmd_list->data->env)) != NULL) // ! add to compare not only agains a env vars but also agains own variables
	{
		if (!*orig_str)
			*orig_str = ft_strdup(str);
		else
		{
			with_space = ft_strjoin(*orig_str, " ");
			free(*orig_str);
			temp = ft_strjoin(with_space, str);
			free(with_space);
			*orig_str = temp;
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
	int i = 0;

	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}