##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

SRC_LIB_MENU     		=		Menu.cpp	\
								../../Core/DLLoader.cpp

OBJ_LIB_MENU     		=		$(SRC_LIB_MENU:.cpp=.o)

NAME_LIB_MENU			=		arcade_menu.so

CPPFLAGS				=		-I ../../../include/Games/Menu	\
								-I ../../../include/Games		\
								-I ../../../include/			\
								-I ../../../include/Graphics	\
								-I ../../../include/Core		\

CXXFLAGS				=		-fPIC -std=c++20 -Wall -Wextra -pedantic -fno-gnu-unique

LDFLAGS					=		-shared -rdynamic

CXX						=		g++

CP						=		cp

LIB						=	 	lib

all: $(NAME_LIB_MENU)

$(NAME_LIB_MENU): $(OBJ_LIB_MENU)
	$(CXX) -o $(NAME_LIB_MENU) $(OBJ_LIB_MENU) $(LDFLAGS)
	$(CP) $(NAME_LIB_MENU) ../../../$(LIB)

clean:
	$(RM) $(OBJ_LIB_MENU)

fclean: clean
	$(RM) ../../../$(LIB)/$(NAME_LIB_MENU)
	$(RM) $(NAME_LIB_MENU)

debug: CXXFLAGS += -g3
debug: re

re:	fclean all

.PHONY:	all clean fclean re
