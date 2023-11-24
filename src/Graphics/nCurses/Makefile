##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

SRC_LIB_NCURSE     	=		LibraryNCurse.cpp				\
							../../Core/ConfigParser.cpp		\

OBJ_LIB_NCURSE     	=		$(SRC_LIB_NCURSE:.cpp=.o)

NAME_LIB_NCURSE		=		arcade_ncurses.so

CPPFLAGS			=		-I ../../../include/Graphics/nCurses	\
							-I ../../../include/Graphics			\
							-I ../../../include/Core

CXXFLAGS			=		-fPIC -std=c++20 -Wall -Wextra -pedantic -fno-gnu-unique

LIBFLAGS			=		-lncurses -shared

CXX					=		g++

CP					=		cp

LIB					=	 	lib

${NAME_LIB_NCURSE}: $(OBJ_LIB_NCURSE)
	$(CXX) -o $(NAME_LIB_NCURSE) $(OBJ_LIB_NCURSE) $(LIBFLAGS)
	$(CP) $(NAME_LIB_NCURSE) ../../../$(LIB)

all: $(NAME_LIB_NCURSE)

clean:
	$(RM) $(OBJ_LIB_NCURSE)

fclean: clean
	$(RM) ../../../$(LIB)/$(NAME_LIB_NCURSE)
	$(RM) $(NAME_LIB_NCURSE)

re:	fclean all

debug:	LIBFLAGS += -g3
debug: re

.PHONY:	all clean fclean re
