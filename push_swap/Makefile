# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 16:42:02 by mfaucheu          #+#    #+#              #
#    Updated: 2022/02/21 11:40:46 by mfaucheu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/check_input.c \
		src/check_input2.c \
		src/ft_split.c \
		src/main.c \
		src/move_front_to_last.c \
		src/move_last_to_front.c \
		src/print_stacks.c \
		src/resolve_above_three.c \
		src/resolve_above_three2.c \
		src/resolve_above_three3.c \
		src/resolve_above_three4.c \
		src/resolve_above_three5.c \
		src/resolve_three.c \
		src/switch_first_a_b.c \
		src/switch_first_two.c \
		src/utils1.c \
		src/utils2.c \
		src/utils3.c \
		src/utils4.c \
		src/utils5.c \
		src/malloc_error.c \

OBJS = ${SRCS:.c=.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

RM = rm -rf

NAME_EXE = -o push_swap

NAME = push_swap

.c.o:
			gcc -I includes ${FLAGS} -c $< -o ${<:.c=.o}

all :		$(NAME)

$(NAME):	$(OBJS)
			gcc ${FLAGS} ${NAME_EXE} ${OBJS}
			

clean :
			${RM} ${OBJS}

fclean :	clean
			${RM} $(NAME)

re :		fclean all

.PHONY:		all bonus clean fclean re
