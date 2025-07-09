/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:38:29 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/09 14:26:51 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_variables(t_command *new_cmd)
{
	int i = 0;

	while (new_cmd->args[i])
	{
		if (dollar_sign(new_cmd->args[i]))
			expand_variables(&(new_cmd->args[i]), new_cmd->data);
		i++;
	}
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
		free(start);
		free(var);
		(*i)++;
		return ;
	}
	if (var[1] == '?')
		ptr_to_env = ft_strdup(ft_itoa(g_last_exit_status));
	else
	{
		ptr_to_env = is_env_var(var, data->env);
		if (!ptr_to_env)
			ptr_to_env = ft_strdup("");
	}
	context = (t_var_replace){str, var, start, ptr_to_env, i}; 
	replace_var(&context);
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

	temp = ft_strjoin(context->start, context->ptr_to_env);
	free(context->start);
	if ((*context->str)[*context->i + ft_strlen(context->var)] != '\0')
		end = ft_strdup(&(*context->str)[*context->i + ft_strlen(context->var)]);
	else
		end = ft_strdup("");
	if (context->var[1] == '?')
		free(context->ptr_to_env);
	free(*context->str);
	*context->str = ft_strjoin(temp, end);
	*context->i = 0;
	free(context->var);
	free(end);
	free(temp);
}

