# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/30 16:06:32 by jozefpluta        #+#    #+#              #
#    Updated: 2025/07/28 15:23:27 by huahmad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = minishell	
CC = cc
CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -lreadline
SRC = \
mini_utils/data_init.c \
mini_utils/env_var.c \
mini_utils/free_functions.c \
minishell.c \
mini_utils/minishell_utils.c \
parsing/quotes_check.c \
parsing/create_redir_list.c \
parsing/create_command_list.c \
parsing/create_command_list_utils.c \
parsing/create_command_list_utils2.c \
execution/execution.c \
execution/execution2.c \
builtins/echo.c \
builtins/builtins.c \
builtins/pwd.c \
builtins/cd.c \
builtins/cd_utils.c \
builtins/export.c \
builtins/export_utils.c \
builtins/unset.c \
builtins/exit.c \
pipes/piping.c \
pipes/redirections.c \
execution/exbuil.c \
execution/exec.c \
pipes/inpredir.c \
pipes/heredoc.c \
parsing/expansion.c \
parsing/handeling.c \
pipes/pipe_child.c \
mini_utils/env_var_utils.c \
mini_utils/syntax_check.c \
pipes/heredocutil.c \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

EXEC = minishell

# Default target
all: $(LIBFT) $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(EXEC)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c -g $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

# Clean up generated files
clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

cl:
	rm -f *.txt

# Remove everything (clean + remove executable)
fclean: clean
	rm -f $(EXEC)
	make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all
