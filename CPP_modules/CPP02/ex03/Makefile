# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/24 11:14:51 by mfaucheu          #+#    #+#              #
#    Updated: 2022/06/26 21:02:14 by mfaucheu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsp

SRCS = main.cpp Fixed.cpp Point.cpp bsp.cpp

OBJS = $(SRCS:.cpp=.o)

FLAGS = -std=c++98 -Wall -Werror -Wextra -g

CC = c++

RM = rm -rf

%.o: %.cpp
				$(CC) $(FLAGS) -c -o $@ $<

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re