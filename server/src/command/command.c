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
    char *str = calloc(server->map->width * server->map->high, sizeof(char));

    for (size_t i = 0; server->map->map[i] ; i++) {
        strcat(str, server->map->map[i]);
    }
    dprintf(play->socket_fd, "MAP %ld %ld %s \n", server->map->width, server->map->high, str);
}

void ready(server_t *server, player_t *play)
{
    play->ready = true;
}

void fire(server_t *server, player_t *play)
{
    // int actived = atoi(stats);
    // if (actived < 0)
    //     return;
    // if (actived > 1)
    //     play->active_jetpack = true;
    // play->active_jetpack = false;
}
