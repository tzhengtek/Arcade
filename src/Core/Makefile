##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

SRC					= 		Main.cpp			\
							DLLoader.cpp		\
							ConfigParser.cpp	\
							Core.cpp			\
							Error.cpp

OBJ					=		$(SRC:.cpp=.o)

NAME				=		arcade

CPPFLAGS			=		-I ../../include					\
							-I ../../include/Core				\
							-I ../../include/Graphics			\
							-I ../../include/Graphics/SFML		\
							-I ../../include/Graphics/SDL2		\
							-I ../../include/Graphics/nCurses	\
							-I ../../include/Games/Snake		\
							-I ../../include/Games/Menu			\
							-I ../../include/Games				\

LDFLAGS				=		-ldl -rdynamic

CXXFLAGS			=		-fPIC -std=c++20 -Wall -Wextra -pedantic -fno-gnu-unique

CXX					=		g++

MV					=		mv

all: 	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)
	$(MV) $(NAME) ../../

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../../$(NAME)

debug:	CXXFLAGS += -g3
debug: re

re:	fclean all

.PHONY:	all clean fclean re
