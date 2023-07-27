# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 03:03:58 by bel-idri          #+#    #+#              #
#    Updated: 2023/07/27 20:27:08 by bel-idri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

NAME_BONUS = minishell_bonus

SRCS = mandatory/main.c \
		mandatory/execution/builtins/my_cd.c \
		mandatory/execution/builtins/my_echo.c \
		mandatory/execution/helper.c \
		mandatory/execution/builtins/my_env.c \
		mandatory/execution/builtins/my_pwd.c \
		mandatory/execution/builtins/my_unset.c \
		mandatory/execution/builtins/my_exit.c \
		mandatory/execution/builtins/my_export.c \
		mandatory/execution/builtins/pipe.c \
		mandatory/parsing/parsing.c

SRCS_BONUS = bonus/main_bonus.c \
	# bonus/execution/tttttt.c \
	# bonus/parsing/ttttt.c \

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
	libft/ft_strcmp.c \
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

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

OBJS_LIBFT = $(SRCS_LIBFT:.c=.o)

CC = cc

# CFLAGS = -Wall -Wextra -Werror -I/goinfre/bel-idri/.brew/opt/readline/include		#---On Bilal Mac---#
CFLAGS = -Wall -Wextra -Werror -I/readline/include  #-g -fsanitize=address

# RLFLAGES = -lreadline -lhistory -L/goinfre/bel-idri/.brew/opt/readline/lib		#---On Bilal Mac---#
RLFLAGES = -lreadline

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS_LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(RLFLAGES) $(OBJS) $(OBJS_LIBFT)  -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_LIBFT) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(RLFLAGES) $(OBJS_BONUS) $(OBJS_LIBFT) -o $(NAME_BONUS)

%.o: %.c minishell_bonus.h
	$(CC) $(CFLAGS) -c $<

%libft/.o: %libft/.o libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) $(OBJS_LIBFT)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS) $(NAME_LIBFT)

re: fclean all

.PHONY: all clean fclean re
