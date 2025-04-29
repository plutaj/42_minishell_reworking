NAME = libft.a

SOURCES = \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strcpy.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strmapi.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_itoa.c \
	ft_memccpy.c \
	ft_memset.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	ft_printf/ft_printf.c \
	ft_printf/functions.c \
	ft_printf/functions2.c \

SOURCES += $(GET_NEXT_LINE_SRC)

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror
CC = cc
AR = ar

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) rcs $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f *.so

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
