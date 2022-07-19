##
## EPITECH PROJECT, 2022
## Jetpack2Tek3
## File description:
## Makefile
##

MAIN	=	src/main.c \
			src/connection/network.c \
			src/connection/client/client_connetion.c \
			src/connection/client/read_data.c \
			src/error/setup_map.c \
			src/error/setup_and_check_args.c \
			src/error/verify_map.c \
			src/list_chain_init.c \
			src/server.c\
			src/command/command.c

SRC	=

OBJ	=	$(MAIN:.c=.o) $(SRC:.c=.o)

NAME	=	 serverJ2T3

LDFLAGS	=

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
