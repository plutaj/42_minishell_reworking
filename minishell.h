/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:28:39 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/20 17:46:00 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_data			t_data;
typedef struct s_command		t_command;
typedef struct s_redir      	t_redir;
typedef enum e_redir_type		t_redir_type;

/* --- tokens --- */
typedef enum e_redir_type
{
    REDIR_INPUT,    // <
    REDIR_OUTPUT,   // >
    REDIR_APPEND,   // >>
    REDIR_HEREDOC   // <<
} 				t_redir_type;

/* --- structs --- */
typedef struct s_redir
{
    t_redir_type	type;
    char			*file_or_limiter;
    struct s_redir	*next;
}				t_redir;

/* This struct represent node of commands */
typedef struct s_command
{
    char				**args;
    int                 arg_i;
    t_redir				*redir;
	t_data				*data;
    struct s_command	*next;
}				t_command;

/* This structure holds all general data about a shell */
typedef struct s_data
{
	char			**env;
	char			*input;
	char			*current_path;
	t_command		*cmd_list;
	int				is_single;
	int				is_double;
}				t_data;

/* data_init.c */
void	    init_data(t_data *data, char **envp);
void	    get_path(t_data *data);
void	    set_data_to_default(t_data *data);

/* env_var.c */
char	    **copy_envp(char **envp);
char		*is_env_var(char *input, char **envp);
void	    update_env_var(char **envp, const char *key, const char *value);
void		strncpy_until_char(char *dest, const char *src, char stop_char);
void        print_env(char **env);

/* free_functions.c */
void	    free_2d_array(char **arr);

/* minishell.c */
void	    print_linked_list(t_command *cmd_list); // for printing purposes
int			only_spaces(const char *s);

/* PARSING ____________________________________________________*/
/* quotes_check.c */
int		    check_for_quotes(t_data *data);

/* create_redir_list.c */
int         check_for_redir(char *arg);
void	    create_redir_list(t_data *data);
void		add_redir_node(char **args, t_command *cmd_list);

/* create_command_list.c */
void	    create_command_list(t_data *data);
t_command	*split_args_and_redirs(t_command *new_cmd, char *s);
int         starts_with_quote(const char *s);
int         ends_with_quote(const char *s, char quote);

/* EXECUTION ___________________________________________________*/
/* execution.c */
void        execution(t_data *data);
int         is_builtin(t_command *cmd_list);
void        is_external(t_data *data, t_command *cmd_list);
char		*find_command_in_path(char	*cmd);
char		*concatenate_paths(char *dir, char *cmd);
int			execute_command(char *full_path, char **args, char **env);

/* BUILTINS ___________________________________________________*/
/* echo.c */
char	    *expand_variables(char *str, char **envp);
char	    *process_arg(char *arg, t_command *cmd_list);
char	    *convert_to_string(t_command *cmd_list, int start);
void	    cmd_echo_exec(t_command *cmd_list, int start, int is_newline);
int	        all_n_flag(char *arg);
void	    cmd_echo(t_command *cmd_list);
char        *get_env_value(char *key, char **envp);
char	    *append_char(char *res, char c);
char	    *expand_var(char *arg, int *i, char *res, t_command *cmd_list);

// void	    cmd_echo(t_command *cmd_list);
// void	    cmd_echo_exec(t_command *cmd_list, int is_newline);
// char	    *convert_to_string(t_command *cmd_list, int is_newline);
// void	    put_variable(int i, t_command *cmd_list, char **orig_str);
// int		    dollar_sign(char *str);

/* builtins.c */
int		    builtin(t_command *cmd_list);
int         builtin2(t_command *cmd_list);

/* pwd.c */
void        cmd_pwd(t_data *data);

/* cd.c */
void        cmd_cd(t_data *data);
char        *append_char_to_str(char *str, char c);
int         list_directory_contents(char *str, const char *path);
int         count_slash(char *str);
void	    cmd_cd_dir(t_data *data);

