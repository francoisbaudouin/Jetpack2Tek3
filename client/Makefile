##
## EPITECH PROJECT, 2020
## aurele.nicolas@epitech.eu
## File description:
## Makefile
##

MAIN	=	src/main.c

SRC		=	src/split_str.c		\
			src/connection.c	\
			src/cli_to_serv.c 	\
			src/cmd.c \
			src/csfml.c \
			src/init_map.c \

OBJ	=	$(MAIN:.c=.o) $(SRC:.c=.o)

NAME	=	clientJ2T3

LDFLAGS	=	-lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window -lpthread

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
