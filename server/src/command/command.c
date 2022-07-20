/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** command
*/

#include "command.h"

void authentication(server_t *server, player_t *play, char **str_command)
{
    (void) str_command;
    (void) server;
    dprintf(play->socket_fd, "ID %d\n", play->id);
}

void map(server_t *server, player_t *play, char **str_command)
{
    (void) str_command;
    char *str = calloc(server->map->width * server->map->high, sizeof(char));

    for (size_t i = 0; server->map->map[i] ; i++) {
        strncat(str, server->map->map[i], strlen(server->map->map[i])-1);
    }
    dprintf(play->socket_fd, "MAP %ld %ld %s \n", server->map->width,
        server->map->high, str);
}

void ready(server_t *server, player_t *play, char **str_command)
{
    (void) server;
    (void) str_command;
    play->ready = true;
}

void fire(server_t *server, player_t *play, char **str_command)
{
    (void) server;
    sleep(1);
    if (strcmp(str_command[1], "0") == 0) {
        play->jetpack = false;
        return;
    }
    if (strcmp(str_command[1], "1") == 0) {
        play->jetpack = true;
        return;
    }
}
