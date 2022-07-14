/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** client_connetion
*/

#include "server.h"

static void init_player_one(client_t *client)
{
    client->p1.connected = true;
    client->p1.money = 0;
    client->p1.pos_x = 0;
    client->p1.pos_y = 0;
    client->p1.ready = true;
}

static void init_player_two(client_t *client)
{
    client->p1.connected = true;
    client->p1.money = 0;
    client->p1.pos_x = 0;
    client->p1.pos_y = 0;
    client->p1.ready = true;
}

static bool new_client_player_one(server_t *server, client_t *client)
{
    client->p1.socket_fd = accept(server->socket_fd_server, &server->socket_addr, server->socket_size);
    if (client->p1.socket_fd == -1) {
        printf("Server, player 1, accept fail");
        return (false);
    }
    init_player_one(client);
    return (true);
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


bool new_client_connection(server_t *server, client_t *client)
{
    switch (client->nb_player) {
    case (0):
        if (new_client_player_two(server, client) == false)
            return (false);
        break;
    case (1):
        if (new_client_player_two(server, client) == false)
            return (false);
    default:
        break;
    }
    return (true);
}