/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:44:45 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/17 20:20:50 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_list(t_redir *redir)
{
	while (redir)
	{
		if (!redir->file_or_limiter || !*redir->file_or_limiter)
		{
			write(2, "minishell: syntax error near unexpected token `newline'\n", 57);
			g_last_exit_status = 258;
			return (0);
		}

		// Detect weird redirection target (e.g., another redirection symbol)
		if (redir->file_or_limiter[0] == '>' || redir->file_or_limiter[0] == '<'
			|| redir->file_or_limiter[0] == '|')
		{
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, redir->file_or_limiter, ft_strlen(redir->file_or_limiter));
			write(2, "\n", 2);
            g_last_exit_status = 258;
			return (0);
		}
		redir = redir->next;
	}
	return (1);
}

int	check_syntax(t_data *data)
{
	t_command *cmd = data->cmd_list;

	// Special case: starts with pipe
	if (cmd && (!cmd->args || !cmd->args[0]))
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		g_last_exit_status = 258;
		return (0);
	}
    else if (cmd->args[0][0] == '\0')
    {
        g_last_exit_status = 0;
        return (0);
    }
	while (cmd)
	{
		// Check empty command between pipes
		if (!cmd->args || !cmd->args[0])
		{
			write(2, "minishell: syntax error near unexpected token `|'\n", 51);
			g_last_exit_status = 258;
			return (0);
		}
		// Check for malformed redirections
		if (!check_redir_list(cmd->redir))
			return (0);

		cmd = cmd->next;
	}
	return (1);
}
