/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** command
*/

#ifndef COMMAND_H_
#define COMMAND_H_
#include "server.h"

typedef struct commands {
	char *key;
	void (*ptr)();
} command_t;

command_t commands[] {
	{"ID",},
	{"MAP",},
	{"READY",},
	{"FIRE",},
	{"START",},
	{"PLAYER",},
	{"COIN",},
	{"FINISH",},
	{"0", NULL}
};

void id(server_t *server);
void map(server_t *server);
void ready(server_t *server);
void fire(server_t *server);
void start(server_t *server);
void player(server_t *server);
void coin(server_t *server);
void finish(server_t *server);

#endif /* !COMMAND_H_ */
