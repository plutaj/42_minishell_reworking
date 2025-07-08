/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:38:29 by jpluta            #+#    #+#             */
/*   Updated: 2025/07/08 18:04:28 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_var(char **str, char *var, char *start, char *ptr_to_env, int *i);
int		skip_invalid_var(char *start, char *var);

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

char	*extract_var(char *str)
{
	int		i;
	char	*new_str;

	i = 1;
	if (str[i] == '?')
	{
		new_str = ft_substr(str, 0, 2);
		return (new_str);
	}
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '\'' || str[i] == '"' || str[i] == '\0')
			break ;
		i++;
	}
	new_str = ft_substr(str, 0, i);
	return (new_str);
}

void	expand_variables(char **str, t_data *data)
{
	char	*ptr_to_env;
	char	*var;
	char	*start;
	int		i;
	int		is_single_q;

	i = 0;
	is_single_q = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\'')
			is_single_q = !is_single_q;
		if ((*str)[i] == '$' && !is_single_q)
		{
			start = ft_substr(*str, 0, i);
			var = extract_var(&(*str)[i]);
			if (skip_invalid_var(start, var))
			{
				i++;
				continue ;
			}
			if (var[1] == '?')
				ptr_to_env = ft_strdup(ft_itoa(g_last_exit_status));
			else
			{
				ptr_to_env = is_env_var(var, data->env);
				if (!ptr_to_env)
					ptr_to_env = ft_strdup("");
			}
			replace_var(str, var, start, ptr_to_env, &i);
			continue ;
		}
		i++;
	}
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

void	replace_var(char **str, char *var, char *start, char *ptr_to_env, int *i)
{
	char	*temp;
	char	*end;

	temp = ft_strjoin(start, ptr_to_env);
	free(start);
	if ((*str)[*i + ft_strlen(var)] != '\0')
		end = ft_strdup(&(*str)[*i + ft_strlen(var)]);
	else
		end = ft_strdup("");
	if (var[1] == '?')
		free(ptr_to_env);
	free(*str);
	*str = ft_strjoin(temp, end);
	*i = 0;
	free(var);
	if (end)
		free(end);
	free(temp);
}

// void	expand_variables(char **str, t_data *data)
// {
// 	char	*ptr_to_env;
// 	char	*var;
// 	char	*start;
// 	char	*temp;
// 	int		i;
// 	int		is_single_q;

// 	i = 0;
// 	is_single_q = 0;
// 	while ((*str)[i] != '\0')
// 	{
// 		if ((*str)[i] == '\'')
// 		{
// 			if (!is_single_q)
// 				is_single_q = 1;
// 			else
// 				is_single_q = 0;
// 		}
// 		if ((*str)[i] == '$' && !is_single_q)
// 		{
// 			start = ft_substr(*str, 0, i);
// 			var = extract_var(&(*str)[i]);
// 			if (var[1] == '\0')
// 			{
// 				if (*start)
// 					free(start);
// 				if (*var)
// 					free(var);
// 				i++;
// 				continue ;
// 			}
// 			if (var[1] == '?')
// 				ptr_to_env = ft_strdup(ft_itoa(g_last_exit_status));
// 			else
// 			{
// 				ptr_to_env = is_env_var(var, data->env);
// 				if (!ptr_to_env)
// 					ptr_to_env = ft_strdup("");
// 			}
// 			temp = ft_strjoin(start, ptr_to_env);
// 			free(start);
// 			if ((*str)[i + (ft_strlen(var))] != '\0')
// 				start = ft_strdup(&(*str)[i + ft_strlen(var)]);
// 			else
// 				start = ft_strdup("");
// 			if (var[1] == '?')
// 				free(ptr_to_env);
// 			free(*str);
// 			*str = ft_strjoin(temp, start);
// 			i = 0;
// 			free(var);
// 			if (start)
// 				free(start);
// 			free(temp);
// 			continue ;
// 		}
// 		i++;
// 	}
// }
