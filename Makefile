##
## EPITECH PROJECT, 2020
## aurele.nicolas@epitech.eu
## File description:
## Makefile
##

all: client server

client:
	make -C client/ all
	cp client/clientJ2T3 ./

server:
	make -C server/ all
	cp server/serverJ2T3 ./

clean:
	make -C client/ clean
	make -C server/ clean
	rm clientJ2T3
	rm serverJ2T3

fclean: clean
	make -C server/ fclean
	make -C client/ fclean

re:	fclean all

tests_run:
	$(MAKE) -C tests/
	./tests/tests_units_tests

debug:  CFLAGS += -g

.PHONY	:	all clean fclean re client server
