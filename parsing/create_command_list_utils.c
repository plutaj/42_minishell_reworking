/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:38:29 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/23 17:41:49 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_variables(t_command *new_cmd)
{
	int	i;

	i = 0;
	while (new_cmd->args[i])
	{
		if (dollar_sign(new_cmd->args[i]))
			expand_variables(&(new_cmd->args[i]), new_cmd->data);
		i++;
	}
}

char	*resolve_variable_value(char *var, t_data *data)
{
	char	*tmp;
	char	*result;

	if (var[1] == '?')
	{
		tmp = ft_itoa(g_last_exit_status);
		result = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		result = is_env_var(var, data->env);
		if (!result)
			result = ft_strdup("");
	}
	return (result);
}

void	handle_variable_expansion(char **str, t_data *data, int *i)
{
	char			*start;
	char			*var;
	char			*ptr_to_env;
	t_var_replace	context;

	start = ft_substr(*str, 0, *i);
	var = extract_var(&(*str)[*i]);
	if (skip_invalid_var(start, var))
	{
		(*i)++;
		return ;
	}
	ptr_to_env = resolve_variable_value(var, data);
	context = (t_var_replace){str, var, start, ptr_to_env, i};
	replace_var(&context);
	free (ptr_to_env);
}

int	skip_invalid_var(char *start, char *var)
{
	if (var[1] == '\0')
	{
		if (*start)
			free(start);
		if (*var)
			free(var);
		return (1);
	}
	return (0);
}

void	replace_var(t_var_replace *context)
{
	char	*temp;
	char	*end;
	size_t	start_len;
	size_t	value_len;

	start_len = ft_strlen(context->start);
	value_len = ft_strlen(context->ptr_to_env);
	temp = ft_strjoin(context->start, context->ptr_to_env);
	free(context->start);
	if ((*context->str)[*context->i + ft_strlen(context->var)] != '\0')
		end = ft_strdup(&(*context->str)[*context->i
				+ ft_strlen(context->var)]);
	else
		end = ft_strdup("");
	free(*context->str);
	*context->str = ft_strjoin(temp, end);
	if (context->var[1] == '?')
		free(context->ptr_to_env);
	*context->i = start_len + value_len - 1;
	free(context->var);
	free(end);
	free(temp);
}
