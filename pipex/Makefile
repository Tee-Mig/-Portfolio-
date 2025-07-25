# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 21:00:51 by mfaucheu          #+#    #+#              #
#    Updated: 2022/03/29 16:40:14 by mfaucheu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BONUS = pipex_bonus

SRCS =	src/pipex.c \
		src/ft_parsing.c \
		src/ft_process.c \
		src/ft_process2.c \
		src/find_nb_arg.c \
		src/utils.c \
		src/ft_split.c \
		src/process_child1.c \
		src/process_child2.c 

SRCS_BONUS =	src_bonus/pipex_bonus.c \
				src_bonus/ft_parsing_bonus.c \
				src_bonus/ft_process_bonus.c \
				src_bonus/ft_fonctions_process.c \
				src_bonus/ft_fonctions_process2.c \
				src_bonus/ft_fonctions_process3.c \
				src_bonus/find_nb_arg.c \
				src_bonus/utils.c \
				src_bonus/utils2.c \
				src_bonus/utils3.c \
				src_bonus/ft_split.c \
				src_bonus/exec_command.c


OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = clang

RM = rm -rf

%.o: %.c
				$(CC) $(FLAGS) -c -o $@ $<

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -o $(NAME)

bonus:			$(NAME_BONUS)

$(NAME_BONUS):	$(OBJS_BONUS)
				$(CC) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)

re:			fclean all

.PHONY: all bonus clean fclean re