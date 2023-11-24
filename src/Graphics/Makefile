##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

all:
	$(MAKE) -C nCurses
	$(MAKE) -C SDL2
	$(MAKE) -C SFML

clean:
	$(MAKE) clean -C nCurses
	$(MAKE) clean -C SDL2
	$(MAKE) clean -C SFML

fclean: clean
	$(MAKE) fclean -C nCurses
	$(MAKE) fclean -C SDL2
	$(MAKE) fclean -C SFML

debug:
	$(MAKE) debug -C nCurses
	$(MAKE) debug -C SDL2
	$(MAKE) debug -C SFML

re:
	$(MAKE) re -C nCurses
	$(MAKE) re -C SDL2
	$(MAKE) re -C SFML

.PHONY:	all clean fclean re
