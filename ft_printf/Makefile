# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 15:02:39 by mfaucheu          #+#    #+#              #
#    Updated: 2021/12/16 13:19:33 by mfaucheu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c \
		display1.c \
		display2.c \
		display_utils.c \
		display_utils2.c \

SRCS_O =	ft_printf.o \
			display1.o \
			display2.o \
			display_utils.o \
			display_utils2.o \

OBJS = ${FILES:.c=.o}

NAME = libftprintf.a

CC = gcc

FLAGS = -c -Wall -Wextra -Werror

INCLUDES = -I./includes

RM = rm -rf

AR = ar -rcs

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(INCLUDES) $(SRCS)
			${AR} $(NAME) $(OBJS)

all :		$(NAME)

clean :
			${RM} ${SRCS_O}

fclean :	clean
			${RM} $(NAME)

re :		fclean all

.PHONY:		all bonus clean fclean re