NAME = stackTests

SRC = stacks_tests.cpp

INC =	stack.hpp

OBJ = $(addprefix obj/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

CXX = c++

RM = rm -rf

MKDIR_P = mkdir -p

OBJ_DIR = obj

all:		$(OBJ_DIR) $(NAME)

obj/%.o:	%.cpp  $(INC)
			$(CXX) $(CXXFLAGS) -I/usr/include -c $< -o $@

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $(OBJ) -I/usr/include -o $@ 
		
$(OBJ_DIR):
			$(MKDIR_P) $@

clean:
			$(RM) $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re bonus