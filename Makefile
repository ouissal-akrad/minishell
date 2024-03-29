# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 03:03:58 by bel-idri          #+#    #+#              #
#    Updated: 2023/08/10 18:10:13 by ouakrad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
		main_helper_1.c \
		main_helper_2.c \
		execution/builtins/my_cd/my_cd.c \
		execution/builtins/my_cd/cd_utils.c \
		execution/builtins/my_cd/my_cd_helper.c \
		execution/builtins/my_echo.c \
		execution/builtins/my_env/my_env.c \
		execution/builtins/my_env/env_utils.c \
		execution/builtins/my_pwd.c \
		execution/builtins/my_unset.c \
		execution/builtins/my_exit.c \
		execution/builtins/my_export/my_export.c \
		execution/builtins/my_export/check.c \
		execution/builtins/my_export/count.c \
		execution/builtins/my_export/cpy_ex.c \
		execution/builtins/my_export/helper_ex.c \
		execution/commands/execution_utils.c \
		execution/commands/multiple_cmd.c \
		execution/commands/one_cmd.c \
		execution/utils/error.c \
		execution/utils/leaks.c \
		execution/utils/helper.c \
		execution/utils/lib.c \
		parsing/add_tokens.c \
		parsing/count_tokens.c \
		parsing/create_node.c \
		parsing/expanding.c \
		parsing/helpers.c \
		parsing/open_file_helper.c \
		parsing/open_files.c \
		parsing/open_hdoc.c \
		parsing/remove_null.c \
		parsing/is_a_dir.c \
		parsing/split_expanding.c \
		parsing/syntax_error_helper.c \
		parsing/lexar.c \
		parsing/syntax_error.c \
		parsing/signals.c \

SRCS_LIBFT = libft/ft_atoi.c \
	libft/ft_bzero.c \
	libft/ft_calloc.c \
	libft/ft_isalnum.c \
	libft/ft_isalpha.c \
	libft/ft_isascii.c \
	libft/ft_isdigit.c \
	libft/ft_isprint.c \
	libft/ft_itoa.c \
	libft/ft_memchr.c \
	libft/ft_memcmp.c \
	libft/ft_memcpy.c \
	libft/ft_memmove.c \
	libft/ft_memset.c \
	libft/ft_putchar_fd.c \
	libft/ft_putendl_fd.c \
	libft/ft_putnbr_fd.c \
	libft/ft_putstr_fd.c \
	libft/ft_split.c \
	libft/ft_strchr.c \
	libft/ft_strdup.c \
	libft/ft_striteri.c \
	libft/ft_strjoin.c \
	libft/ft_strlcat.c \
	libft/ft_strlcpy.c \
	libft/ft_strlen.c \
	libft/ft_strmapi.c \
	libft/ft_strncmp.c \
	libft/ft_strnstr.c \
	libft/ft_strrchr.c \
	libft/ft_strtrim.c \
	libft/ft_substr.c \
	libft/ft_tolower.c \
	libft/ft_toupper.c \
	libft/ft_lstadd_back.c \
	libft/ft_lstadd_front.c \
	libft/ft_lstclear.c \
	libft/ft_lstdelone.c \
	libft/ft_lstiter.c \
	libft/ft_lstlast.c \
	libft/ft_lstmap.c \
	libft/ft_lstnew.c \
	libft/ft_lstsize.c \

OBJS = $(SRCS:.c=.o)

OBJS_LIBFT = $(SRCS_LIBFT:.c=.o)

CC = cc

USER = $(shell whoami)

CFLAGS = -Wall -Wextra -Werror -I/Users/${USER}/.brew/opt/readline/include #-g -fsanitize=address

RLFLAGES = -lreadline -lhistory -L/Users/${USER}/.brew/opt/readline/lib

RM = rm -f


all: $(NAME)

$(NAME): $(OBJS_LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(RLFLAGES) $(OBJS) $(OBJS_LIBFT)  -o $(NAME)

%.o: %.c minishell.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@


%libft/.o: %libft/.o libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	$(RM) $(OBJS) $(OBJS_LIBFT)

fclean: clean
	$(RM) $(NAME) $(NAME_LIBFT)

re: fclean all

.PHONY: all clean fclean re
