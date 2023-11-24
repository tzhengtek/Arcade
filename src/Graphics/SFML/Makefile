##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

SRC_LIB_SFML     	=		LibrarySFML.cpp				\
							../../Core/ConfigParser.cpp	\

OBJ_LIB_SFML     	=		$(SRC_LIB_SFML:.cpp=.o)

NAME_LIB_SFML		=		arcade_sfml.so

CPPFLAGS			=		-I ../../../include/Graphics/SFML	\
							-I ../../../include/Graphics		\
							-I ../../../include					\
							-I ../../../include/Core

CXXFLAGS			=		-fPIC -std=c++20 -Wall -Wextra -pedantic -Ofast -fno-gnu-unique

LIBFLAGS			=		-lsfml-graphics -lsfml-window -lsfml-system -shared

CXX					=		g++

CP					=		cp

LIB					=	 	lib

all: $(NAME_LIB_SFML)

$(NAME_LIB_SFML): $(OBJ_LIB_SFML)
	$(CXX) -o $(NAME_LIB_SFML) $(OBJ_LIB_SFML) $(LIBFLAGS)
	$(CP) $(NAME_LIB_SFML) ../../../$(LIB)

clean:
	$(RM) $(OBJ_LIB_SFML)

fclean: clean
	$(RM) ../../../$(LIB)/$(NAME_LIB_SFML)
	$(RM) $(NAME_LIB_SFML)

debug:	CXXFLAGS += -g3
debug: re

re:	fclean all

.PHONY:	all clean fclean re
