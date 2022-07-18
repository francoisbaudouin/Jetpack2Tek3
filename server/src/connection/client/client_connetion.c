/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** client_connetion
*/

#include "server.h"

static void *init_player(player_t *player, int id)
{
    player->id = id;
    player->pos_x = 0;
    player->pos_y = 0;
    player->money = 0;
    player->connected = true;
    player->ready = false;
    player->active_jetpack = false;
    return (player);
}

static bool add_player(server_t *server, element_t *elem, int id)
{
    elem->player = malloc(sizeof(player_t));
    elem->player->socket_fd = accept(server->socket_fd_server, &server->socket_addr, server->socket_size);
    if (elem->player->socket_fd == -1) {
        printf("Server, player 2, accept fail");
        return (false);
    }
    elem->player = init_player(elem->player,id);
    return (true);
}

bool new_client_connection(server_t *server, list_t *client)
{
    element_t *data = client->first;
    if (client->size == 0) {
        if (add_player(server, client->first, client->size + 1) == false)
            return (false);
        return (true);
    } else if () {
        
    }
    player_t *player = malloc(sizeof(player_t));
    insertion(client, player);

    return (true);
}
