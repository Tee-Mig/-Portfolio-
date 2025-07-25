NAME = vectorTests
NAME_IT = vectorIteratorTests

SRC = vector_tests
SRC_IT = vector_iterator_tests.cpp

INC =	vector.hpp \
		VectorIterator.hpp \
		ReverseIterator.hpp \
		Traits.hpp

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