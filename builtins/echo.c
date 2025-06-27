/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:19:40 by jpluta            #+#    #+#             */
/*   Updated: 2025/06/27 18:04:56 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_echo(t_command *cmd_list)
{
	if (cmd_list->args[1] == NULL)
	{
		printf("\n");
		g_last_exit_status = 0;
	}
    else if (ft_strcmp(cmd_list->args[1], "-n") == 0)
        cmd_echo_exec(cmd_list, 0);
    else
        cmd_echo_exec(cmd_list, 1);
}

void	cmd_echo_exec(t_command *cmd_list, int is_newline)
{
	char	*str;

	str = convert_to_string(cmd_list, is_newline);
	if (!is_newline)
		printf("%s", str);
	else
		printf("%s\n", str);
	g_last_exit_status = 0;
	free (str);
}

char	*convert_to_string(t_command *cmd_list, int is_newline)
{
	char	*orig_str;
	char	*temp;
	int		i;

	orig_str = NULL;
	temp = NULL;
	if (is_newline)
		i = 1;
	else
		i = 2;
	while (cmd_list->args[i])
	{
		if (orig_str == NULL)
			orig_str = ft_strdup(cmd_list->args[i]);
		else
		{
			temp = ft_strjoin(orig_str, " ");
			free(orig_str);
			orig_str = ft_strjoin(temp, cmd_list->args[i]);
			free(temp);
		}
		i++;
	}
	return (orig_str);
}

int	dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}