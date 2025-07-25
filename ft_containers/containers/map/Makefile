NAME = mapTests
NAME_IT = mapIteratorTests

SRC = map_tests.cpp
# SRC = map_tests2.cpp
SRC_IT = map_iterator_tests.cpp
# SRC = tree_tests.cpp

INC =	map.hpp \
		red_black_tree.hpp \
		MapIterator.hpp \
		MapReverseIterator.hpp \
		utils.hpp

OBJ = $(addprefix obj/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_IT = $(addprefix obj/, $(addsuffix .o, $(notdir $(basename $(SRC_IT)))))

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

it:			$(OBJ_DIR) $(OBJ_IT)
			$(CXX) $(CXXFLAGS) $(OBJ_IT) -I/usr/include -o ${NAME_IT}
		
$(OBJ_DIR):
			$(MKDIR_P) $@

clean:
			$(RM) $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(NAME_IT)

re:			fclean all

.PHONY: all clean fclean re bonus