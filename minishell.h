/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:28:39 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/10 10:28:09 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
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
}				t_command;

/* This structure holds all general data about a shell */
typedef struct s_data
{
	char			**env;
	char			*input;
	char			*current_path;
	t_command		*commands;
	int				is_single;
	int				is_double;
}				t_data;

/* data_init.c */
void	    init_data(t_data *data, char **envp);
void	    get_path(t_data *data);
void	    set_data_to_default(t_data *data);

/* env_var.c */
char	    **copy_envp(char **envp);

/* free_functions.c */
void	    free_2d_array(char **arr);

/* --- minishell.c --- */
void	    print_linked_list(t_command *commands); // for printing purposes
// int         get_index_of_quotes(char *s, t_data *data);

/* quotes_check.c */
int		    check_for_quotes(t_data *data);

/* create_redir_list.c */
char        *check_for_redir(char *arg);
void	    create_redir_list(t_data *data);
void	    add_redir_node(char *p_to_redir, t_data *data);


/* create_command_list.c */
void	    create_command_list(t_data *data);
void		cut_spaces(char **s);
// t_command	*split_args_and_redirs(t_command *new_cmd, char *s);
// int         starts_with_quote(const char *s);
// int         ends_with_quote(const char *s, char quote);


