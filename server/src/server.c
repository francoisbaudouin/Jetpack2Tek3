/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** server
*/

#include "server.h"
#include <signal.h>

static void manage_client(server_t *server, list_t *client)
{
    if (FD_ISSET(server->socket_fd_server, &server->tmp_rfds))
        new_client_connection(server, client);
    else
        read_data_player_command(server, client);
}

static bool is_all_player_ready(server_t *server, list_t *client)
{
    element_t *tmp = client->first;
    
    if(tmp == NULL && tmp->next == NULL)
        return (false);
    
    if(tmp->player->ready == tmp->next->player->ready) {
        server->can_strat_game = true;
        dprintf(tmp->player->socket_fd, "READY\n");
        dprintf(tmp->next->player->socket_fd, "READY\n");
        return (true);
    }
    return (false);
}

static void player_send_data(list_t *client)
{
    element_t *p1;
    element_t *p2;

    if (client->size != 2)
        return;
    p1 = client->first;
    p2 = client->first->next;
    dprintf(p1->player->socket_fd, "PLAYER %d %ld %ld %ld\n", p1->player->id, 
        p1->player->pos_x, p1->player->pos_x, p1->player->score);

    dprintf(p1->player->socket_fd, "PLAYER %d %ld %ld %ld\n", p2->player->id, 
        p2->player->pos_x, p2->player->pos_x, p2->player->score);
    
    dprintf(p2->player->socket_fd, "PLAYER %d %ld %ld %ld\n", p2->player->id, 
        p2->player->pos_x, p2->player->pos_x, p2->player->score);
    
    dprintf(p2->player->socket_fd, "PLAYER %d %ld %ld %ld\n", p1->player->id, 
        p1->player->pos_x, p1->player->pos_x, p1->player->score);
}

static bool loop_game(server_t *server, list_t *client)
{
    (void) server;
    (void) client;
    // is disconnect
    // jetpack;
    // player;
    if (is_all_player_ready(server, client) == true)
        return (false);
    return (true);
}

void running_server(server_t *server)
{
    list_t *client = initialization();
    //signal(SIGINT, (__sighandler_t)(server->server_running = false));
    server->server_running = true;
    while (server->server_running == true) {
        server->tmp_rfds = server->rfds;
        server->tmp_wfds = server->wfds;
        if (select(FD_SETSIZE, &server->tmp_rfds, 
            &server->tmp_wfds, NULL, NULL) == -1) {
            perror("select");
            return;
        }
        player_send_data(client);
        manage_client(server, client);
        if (client->size == 2)
            loop_game(server, client);
    }
}
