/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:28:39 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/29 19:05:38 by jozefpluta       ###   ########.fr       */
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

typedef struct s_data		t_data;
typedef struct s_command	t_command;
typedef struct s_redir      t_redir;
typedef enum e_redir_type	t_redir_type;


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

typedef struct s_command
{
    char				**args;
    t_redir				*redir;
    struct s_command	*next;
}				t_command;

/* This structure holds all general data about a shell */
typedef struct s_data
{
	char		**env;
	char		*input;
	char		*current_path;
	t_command	*cmd_list;
	t_redir		*redir_list;
}				t_data;

/* --- minishell.c --- */
