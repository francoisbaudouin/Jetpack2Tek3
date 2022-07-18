/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** command
*/

#ifndef COMMAND_H_
#define COMMAND_H_
#include "server.h"

void id(server_t *server, player_t *player);
void map(server_t *server, player_t *player);
void ready(server_t *server, player_t *player);
void fire(server_t *server, player_t *player);
void start(server_t *server, player_t *player);
void player(server_t *server, player_t *player);
void coin(server_t *server, player_t *player);
void finish(server_t *server, player_t *player);

typedef struct commands {
	char *key;
	void (*ptr)(server_t*, player_t*);
} command_t;



#endif /* !COMMAND_H_ */
