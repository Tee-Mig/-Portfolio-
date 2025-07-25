# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 20:04:17 by mfaucheu          #+#    #+#              #
#    Updated: 2022/05/15 20:44:10 by mfaucheu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/main.c	\
		src/philo_process.c \
		src/routine_philos.c \
		src/parsing.c \
		src/fill_info.c \
		src/utils.c

OBJS = $(SRCS:.c=.o)

NAME = philo

CC = clang -pthread

FLAGS = -Wall -Werror -Wextra -g

RM = rm -rf

%.o: %.c
				$(CC) $(FLAGS) -pthread -c -o $@ $<

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -o $(NAME)

clean:			
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY: all clean fclean re