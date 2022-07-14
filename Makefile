##
## EPITECH PROJECT, 2020
## aurele.nicolas@epitech.eu
## File description:
## Makefile
##

all: client server

client:
	make -C client/
	cp ./client/clientJ2T3 .

server:
	make -C server/
	cp ./client/serverJ2T3 .

clean:
	make -C server/ clean
	make -C clent/ clean
	rm clientJ2T3
	rm serverJ2T3

fclean: clean
	make -C server/ fclean
	make -C clent/ fclean

re:	fclean all

tests_run:
	$(MAKE) -C tests/
	./tests/tests_units_tests

debug:  CFLAGS += -g

.PHONY	:	all clean fclean re
