##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

all:	graphicals core games

clean:
	$(MAKE) clean -C src/Graphics
	$(MAKE) clean -C src/Core
	$(MAKE) clean -C src/Games

fclean: clean
	$(MAKE) fclean -C src/Graphics
	$(MAKE) fclean -C src/Core
	$(MAKE) fclean -C src/Games

graphicals:
	$(MAKE) -C src/Graphics

core:
	$(MAKE) -C src/Core

games:
	$(MAKE) -C src/Games

debug:
	$(MAKE) debug -C src/Graphics
	$(MAKE) debug -C src/Core
	$(MAKE) debug -C src/Games

re:
	$(MAKE) re -C src/Graphics
	$(MAKE) re -C src/Core
	$(MAKE) re -C src/Games

.PHONY:	all clean fclean re
