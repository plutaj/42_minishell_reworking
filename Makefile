# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/30 16:06:32 by jozefpluta        #+#    #+#              #
#    Updated: 2025/06/29 14:04:50 by jpluta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = minishell	
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
SRC = \
data_init.c \
env_var.c \
free_functions.c \
minishell.c \
minishell_utils.c \
parsing/quotes_check.c \
parsing/create_redir_list.c \
parsing/create_command_list.c \
parsing/create_command_list_utils.c \
execution/execution.c \
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
pipes/inpredir.c \

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

# Remove everything (clean + remove executable)
fclean: clean
	rm -f $(EXEC)
	make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all
