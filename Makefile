##
## EPITECH PROJECT, 2020
## my_defender
## File description:
## makefile
##

SRC	=

MAIN	=	src/main.c	\

TEST_SRC	=

NAME	=	my_defender

TEST_NAME	=	unit_tests

OBJECT	=	$(SRC:.c=.o)

MAIN_OBJECT	=	$(MAIN:.c=.o)

OBJECT_TEST	=	*.gcno	\
				*.gcda	\
				$(TEST_NAME)

CC	=	gcc

# CFLAGS	=	-I./includes/ -Wall -Wextra -Wshadow -L./lib/my/ -lmy

LDFLAGS	=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

TFLAGS	=	--coverage -lcriterion

all:	$(NAME)

$(NAME): $(OBJECT) $(MAIN_OBJECT)
	make -C
	$(CC) -o $(NAME) $(OBJECT) $(MAIN_OBJECT) $(CFLAGS) $(LDFLAGS)

clean:
	make clean -C
	$(RM) $(OBJECT)
	$(RM) $(MAIN_OBJECT)
	$(RM) *.gcda
	$(RM) *.gcno

fclean: clean
	clear
	make fclean -C
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

re:	fclean	all

compile_test:
	make -C
	$(CC) -o $(TEST_NAME) $(SRC) $(TEST_SRC) $(TFLAGS) $(CFLAGS) $(LDFLAGS)

run_test:	fclean compile_test
	./$(TEST_NAME)
	gcovr --exclude tests
