/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** command
*/

#include "command.h"

void authentication(server_t *server, player_t *play)
{
    dprintf(play->socket_fd, "ID %d\n", play->id);
}

void map(server_t *server, player_t *play)
{
    printf("test id\n");
}

void ready(server_t *server, player_t *play)
{
    printf("test id");
}

void fire(server_t *server, player_t *play)
{
    play->active_jetpack = true;
}
