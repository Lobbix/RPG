##
## EPITECH PROJECT, 2021
## stumper
## File description:
## Makefile
##

NAME = 	my_rpg

all: $(NAME)

$(NAME):
	gcc -O3 ./*.c -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -o $(NAME)

clean:
	rm -f $(NAME)

fclean:	clean

re:	fclean all
