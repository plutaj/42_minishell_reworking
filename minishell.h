/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:28:39 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/07/03 12:58:05 by huahmad          ###   ########.fr       */                                                     
/* ************************************************************************** */

#include "libft/libft.h"
#include <dirent.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_data		t_data;
typedef struct s_command	t_command;
typedef struct s_redir		t_redir;
typedef enum e_redir_type	t_redir_type;

extern int					g_last_exit_status;
/* --- tokens --- */
typedef enum e_redir_type
{
	REDIR_INPUT,  // <
	REDIR_OUTPUT, // >
	REDIR_APPEND, // >>
	REDIR_HEREDOC // <<
}							t_redir_type;

/* --- structs --- */
typedef struct s_redir
{
	t_redir_type			type;
	char					*file_or_limiter;
	struct s_redir			*next;
}							t_redir;

/* This struct represent node of commands */
typedef struct s_command
{
	char					**args;
	int arg_i; // how many commands
	t_redir					*redir;
	t_data					*data;
	struct s_command		*next;
}							t_command;

/* This structure holds all general data about a shell */
typedef struct s_data
{
	char					**env;
	char					*input;
	char					*current_path;
	t_command				*cmd_list;
	int						is_single;
	int						is_double;
}							t_data;

/* data_init.c */
void						init_data(t_data *data, char **envp);
void						get_path(t_data *data);
void						set_data_to_default(t_data *data);

/* env_var.c */
char						**copy_envp(char **envp);
char						*is_env_var(char *input, char **envp);
int							update_env_var(char **envp, const char *key,
								const char *value);
void						strncpy_until_char(char *dest, const char *src,
								char stop_char);
void						print_env(char **env);

/* free_functions.c */
void						free_2d_array(char **arr);

/* minishell_utils.c */
void						print_linked_list(t_command *cmd_list);
void						sigint_handler(int signo);
int							only_spaces(const char *s);

/* PARSING ____________________________________________________*/
/* quotes_check.c */
int							check_for_quotes(t_data *data);

/* create_redir_list.c */
int							check_for_redir(char *arg);
void						create_redir_list(t_data *data);
void						add_redir_node(char **args, t_command *cmd_list);
int							redirectinp(t_data *data);
int							redirectout(t_data *data);
int							handle_heredoc(char *limiter);

/* create_command_list.c */
void						create_command_list(t_data *data);
t_command					*split_args_and_redirs(t_command *new_cmd, char *s);
int							starts_with_quote(const char *s);
int							ends_with_quote(const char *s, char quote);
char						*remove_quotes(const char *str);
void						remove_quotes_from_args(char **args);
int							handle_redirections(char *s, int *i, char **args,
								int *j, char *buffer, int *buf_i);
void						handle_quotes(char c, char *quote);
int							handle_spaces(char *s, int *i, char **args, int *j,
								char *buffer, int *buf_i);
void						flush_buffer(char *buffer, char **args, int *j,
								int *buf_i);

/* create_command_list_utils.c */
void						find_variables(t_command *new_cmd);
void						expand_variables(char **str, t_data *data);
char						*extract_var(char *str);

/* execuion/exbuil.c */
int         is_builtin(t_command *cmd_list);
char		*find_command_in_path(char *cmd);
void        is_external(t_data *data, t_command *cmd_list);
char		*search_command_in_path(t_command *cmd_list, t_data *data);

/* execuion/execution.c */
void						execution(t_data *data);
char						*find_command_in_path(char *cmd);
char						*concatenate_paths(char *dir, char *cmd);
int							execute_command(char *full_path, char **args,
								char **env);
void						executepipecmds(t_data *data);
void						update_pipe_fds(int *prev_pipe_read, int pipefd[2],
								int has_next);
int							create_pipe(int pipefd[2]);
int							setup_redirection(int prev_pipe_read, int pipefd[],
								t_command *cmd);
t_command					*temp(int *fd, t_data *data);
int							do_input_redir(t_redir *redir);
void						is_my_external(t_data *data, t_command *cmd_list);
void						execerror(char *full_path, char **args, char **env);

/* builtins/echo.c */
void						cmd_echo(t_command *cmd_list);
void						cmd_echo_exec(t_command *cmd_list, int is_newline);
char						*convert_to_string(t_command *cmd_list,
								int is_newline);
void						put_variable(int i, t_command *cmd_list,
								char **orig_str);
int							dollar_sign(char *str);

/* builtins/export.c */
void						cmd_export(t_data *data);
void						create_env_var(t_data *data, char *var);
int							is_valid_syntax(char *str);

/* builtins/export_utils.c */
void						print_exported_env(char **env);
char						*extract_var_value(char *str);

/* builtins/builtins.c */
int							builtin(t_command *cmd_list);
int							builtin2(t_command *cmd_list);
void						exit_f(t_command *cmd_list);

/* builtins/pwd.c */
void						cmd_pwd(t_data *data);

/* builtins/cd.c */
void						cmd_cd(t_data *data);
void						cmd_cd_dir(t_data *data);

/* builtins/cd_utils.c */
char						*append_char_to_str(char *str, char c);
int							list_directory_contents(char *str,
								const char *path);
int							count_slash(char *str);

/* builtins/unset.c */
void						cmd_unset(t_data *data);
int							count_rows_of_arr(t_data *data);
void						unset_invalid_num_args(void);
