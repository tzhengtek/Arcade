##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

SRC_LIB_SNAKE     	=		LibrarySnake.cpp			\
							../../Core/ConfigParser.cpp

OBJ_LIB_SNAKE     	=		$(SRC_LIB_SNAKE:.cpp=.o)

NAME_LIB_SNAKE		=		arcade_snake.so

CPPFLAGS			=		-I ../../../include/Games/Snake	\
							-I ../../../include/Games		\
							-I ../../../include/Core

CXXFLAGS			=		-fPIC -std=c++20 -Wall -Wextra -pedantic -fno-gnu-unique

LIBFLAGS			=		-shared

CXX					=		g++

CP					=		cp

LIB					=	 	lib

all: $(NAME_LIB_SNAKE)

$(NAME_LIB_SNAKE): $(OBJ_LIB_SNAKE)
	$(CXX) -o $(NAME_LIB_SNAKE) $(OBJ_LIB_SNAKE) $(LIBFLAGS)
	$(CP) $(NAME_LIB_SNAKE) ../../../$(LIB)

clean:
	$(RM) $(OBJ_LIB_SNAKE)

fclean: clean
	$(RM) ../../../$(LIB)/$(NAME_LIB_SNAKE)
	$(RM) $(NAME_LIB_SNAKE)

debug: CXXFLAGS += -g3
debug: re

re:	fclean all

.PHONY:	all clean fclean re
