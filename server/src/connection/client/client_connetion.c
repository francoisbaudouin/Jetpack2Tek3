/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** client_connetion
*/

#include "server.h"

static void init_player(player_t *player, int id)
{
    player->id = id;
    player->pos_x = 1;
    player->pos_y = 1;
    player->money = 0;
    player->connected = true;
    player->ready = false;
    player->jetpack = 0;
    player->score = 0;
}

static player_t *add_player(server_t *server, int id)
{
    player_t *player = malloc(sizeof(player_t));
    player->socket_fd = accept(server->socket_fd_server, 
        (struct sockaddr*)&server->socket_addr, &server->socket_size);
    if (player->socket_fd == -1) {
        printf("Server, accept error\n");
        return (NULL);
    }
    init_player(player, id);
    FD_SET(player->socket_fd, &server->rfds);
    return (player);
}

bool new_client_connection(server_t *server, list_t *client)
{
    if (client->size != 2) {
        insertion(client, add_player(server, client->size + 1));
        return (true);
    }
    printf("Not enough place!\n");
    return (false);
}
