##
## EPITECH PROJECT, 2020
## aurele.nicolas@epitech.eu
## File description:
## Makefile
##

MAIN	=	src/main.c

SRC	=

OBJ	=	$(MAIN:.c=.o) $(SRC:.c=.o)

NAME	=	clientJ2T3

LDFLAGS	=	-lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window

CFLAGS	=	-I./include -Wshadow -Wextra -Wall

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY	:	all clean fclean re
