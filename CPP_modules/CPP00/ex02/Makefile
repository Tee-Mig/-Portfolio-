NAME = dream_job

SRCS =	tests.cpp Account.cpp

INC = Account.hpp

OBJS = $(SRCS:.cpp=.o)

FLAGS = -std=c++98 -Wall -Werror -Wextra -g

CC = c++

RM = rm -rf

%.o: %.cpp $(INC)
				$(CC) $(FLAGS) -c -o $@ $<

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re