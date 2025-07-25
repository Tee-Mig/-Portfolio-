# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naben-za <naben-za@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 18:20:02 by mfaucheu          #+#    #+#              #
#    Updated: 2022/06/02 18:23:53 by naben-za         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/main.c \
		src/free_main.c \
		src/input_main.c \
		src/builtins.c \
		src/token_into_cmd.c \
		src/token_into_cmd2.c \
		src/ft_liste_chainee.c \
		src/ft_liste_chainee2.c \
		src/ft_split.c \
		src/parsing.c \
		src/parsing2.c \
		src/utils.c \
		src/utils2.c \
		src/utils3.c \
		src/utils4.c \
		src/exec_cmd.c \
		src/exec_cmd2.c \
		src/exec_cmd3.c \
		src/exec_cmd4.c \
		src/exec_cmd5.c \
		src/exec_cmd6.c \
		src/signal.c \
		src/ft_heredoc.c \
		src/get_next_line.c \
		src/expand1.c \
		src/expand2.c \
		src/ft_path.c \
		src/builtins1.c \
		src/export1.c \
		src/export2.c \
		src/unset.c \
		src/remove_quote.c

OBJS = ${SRCS:.c=.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror -g #fsanitize=address -g3

RM = rm -rf

NAME = minishell

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all :		$(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME)

clean :
			@${RM} ${OBJS}

fclean :	clean
			@${RM} $(NAME)

re :		fclean all

.PHONY:		all bonus clean fclean re
