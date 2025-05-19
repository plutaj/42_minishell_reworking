/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:19:40 by jpluta            #+#    #+#             */
/*   Updated: 2025/05/19 20:54:08 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_echo(t_command *cmd_list)
{
	int	i = 1;
	int	is_newline = 1;

	while (cmd_list->args[i] && ft_strncmp(cmd_list->args[i], "-n", 2) == 0)
	{
		if (!all_n_flag(cmd_list->args[i]))
			break;
		is_newline = 0;
		i++;
	}
	cmd_echo_exec(cmd_list, i, is_newline);
}

int	all_n_flag(char *arg)
{
	int j = 2;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	cmd_echo_exec(t_command *cmd_list, int start, int is_newline)
{
	char	*output;

    output = convert_to_string(cmd_list, start);
	if (!output)
		output = ft_strdup("");
	if (is_newline)
		printf("%s\n", output);
	else
		printf("%s", output);
	free(output);
}

char	*convert_to_string(t_command *cmd_list, int start)
{
	char	*res = NULL;
	char	*tmp;
	char	*processed;
	int		i = start;

	while (cmd_list->args[i])
	{
		processed = process_arg(cmd_list->args[i], cmd_list);
		if (!processed)
			processed = ft_strdup("");

		if (!res)
			res = processed;
		else
		{
			tmp = ft_strjoin(res, " ");
			free(res);
			res = ft_strjoin(tmp, processed);
			free(tmp);
			free(processed);
		}
		i++;
	}
	return (res);
}

// char	*process_arg(char *arg, t_command *cmd_list)
// {
// 	char	*cleaned;
// 	char	*expanded;

// 	if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
// 		return (ft_substr(arg, 1, ft_strlen(arg) - 2)); // no expansion
// 	else if (arg[0] == '"' && arg[ft_strlen(arg) - 1] == '"')
// 	{
// 		cleaned = ft_substr(arg, 1, ft_strlen(arg) - 2); // strip quotes
// 		expanded = expand_variables(cleaned, cmd_list->data->env);
// 		free(cleaned);
// 		return expanded; // may be empty string — that's OK
// 	}
// 	else
// 	{
// 		return expand_variables(arg, cmd_list->data->env);
// 	}
// }

char	*expand_var(char *arg, int *i, char *res, t_command *cmd_list)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*tmp;

	start = ++(*i);
	while (ft_isalnum(arg[*i]) || arg[*i] == '_')
		(*i)++;
	var_name = ft_substr(arg, start, *i - start);
	var_value = get_env_value(var_name, cmd_list->data->env);
	free(var_name);
	tmp = ft_strjoin(res, var_value ? var_value : "");
	free(res);
	return (tmp);
}

char	*append_char(char *res, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(res, buf);
	free(res);
	return (tmp);
}

char	*process_arg(char *arg, t_command *cmd_list)
{
	char	*res;
	int		i;
	int		in_single;
	int		in_double;

	res = ft_strdup("");
	i = 0;
	in_single = 0;
	in_double = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (arg[i] == '"' && !in_single)
			in_double = !in_double;
		else if (arg[i] == '$' && !in_single)
		{
			res = expand_var(arg, &i, res, cmd_list);
			continue;
		}
		else
			res = append_char(res, arg[i]);
		i++;
	}
	return (res);
}

char	*expand_variables(char *str, char **envp)
{
	int		i = 0;
	int		start;
	char	*res = ft_strdup("");
	char	*var_name;
	char	*var_value;
	char	*temp;

	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			start = ++i;
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			var_name = ft_substr(str, start, i - start);
			var_value = get_env_value(var_name, envp);
			free(var_name);
			temp = ft_strjoin(res, var_value ? var_value : "");
			free(res);
			res = temp;
		}
		else
		{
			char buf[2] = {str[i], '\0'};
			temp = ft_strjoin(res, buf);
			free(res);
			res = temp;
			i++;
		}
	}
	return (res);
}

char *get_env_value(char *key, char **envp)
{
	int		i = 0;
	int		key_len = ft_strlen(key);

	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}