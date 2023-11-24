##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

SRC_LIB_PACMAN     		=		LibraryPacman.cpp			\
								PacEntity.cpp				\
								PathFinder.cpp				\
								../../Core/ConfigParser.cpp	\

OBJ_LIB_PACMAN     		=		$(SRC_LIB_PACMAN:.cpp=.o)

NAME_LIB_PACMAN			=		arcade_pacman.so

CPPFLAGS				=		-I ../../../include/Games/Pacman	\
								-I ../../../include/Games			\
								-I ../../../include/Core

CXXFLAGS				=		-fPIC -std=c++20 -Wall -Wextra -pedantic -fno-gnu-unique

LIBFLAGS				=		-shared

CXX						=		g++

CP						=		cp

LIB						=	 	lib

all: $(NAME_LIB_PACMAN)

$(NAME_LIB_PACMAN): $(OBJ_LIB_PACMAN)
	$(CXX) -o $(NAME_LIB_PACMAN) $(OBJ_LIB_PACMAN) $(LIBFLAGS)
	$(CP) $(NAME_LIB_PACMAN) ../../../$(LIB)

clean:
	$(RM) $(OBJ_LIB_PACMAN)

fclean: clean
	$(RM) ../../../$(LIB)/$(NAME_LIB_PACMAN)
	$(RM) $(NAME_LIB_PACMAN)

debug: CXXFLAGS += -g3
debug: re

re:	fclean all

.PHONY:	all clean fclean re
