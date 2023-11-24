##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

SRC_LIB_SDL2     	=		LibrarySDL2.cpp					\
							../../Core/ConfigParser.cpp		\

OBJ_LIB_SDL2     	=		$(SRC_LIB_SDL2:.cpp=.o)

NAME_LIB_SDL2		=		arcade_sdl2.so

CPPFLAGS			=		-I ../../../include/Graphics/SDL2 	\
							-I ../../../include/Graphics		\
							-I ../../../include/Core			\
							-I ../../../include/

CXXFLAGS			=		-fPIC -std=c++20 -Wall -Wextra -pedantic -fno-gnu-unique

LIBFLAGS			=		-lSDL2 -lSDL2_ttf -lSDL2_image -shared

CXX					=		g++

CP					=		cp

LIB					=	 	lib

all: $(NAME_LIB_SDL2)

$(NAME_LIB_SDL2): $(OBJ_LIB_SDL2)
	$(CXX) -o $(NAME_LIB_SDL2) $(OBJ_LIB_SDL2) $(LIBFLAGS)
	$(CP) $(NAME_LIB_SDL2) ../../../$(LIB)

clean:
	$(RM) $(OBJ_LIB_SDL2)

fclean: clean
	$(RM) ../../../$(LIB)/$(NAME_LIB_SDL2)
	$(RM) $(NAME_LIB_SDL2)

debug: CXXFLAGS += -g3
debug: re

re:	fclean all

.PHONY:	all clean fclean re
