/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** client_connetion
*/

#include "server.h"

static void *init_player(player_t *player)
{
    player->id = 0;
    player->socket_fd = 0;
    player->pos_x = 0;
    player->pos_y = 0;
    player->money = 0;
    player->connected = true;
    player->ready = false;
    player->active_jetpack = false;
    return (player);
}

static bool new_client_player_two(server_t *server, client_t *client)
{
    client->p2.socket_fd = accept(server->socket_fd_server, &server->socket_addr, server->socket_size);
    if (client->p2.socket_fd == -1) {
        printf("Server, player 2, accept fail");
        return (false);
    }
    init_player_two(client);
    return (true);
}

bool new_client_connection(server_t *server, list_t *client)
{
    element_t *data = client->first;

    while (data->next != NULL)  {
        data = data->next;
    }

    return (true);
}
