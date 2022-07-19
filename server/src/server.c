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
        return (true);
    }
    return (false);
}

static bool loop_game(server_t *server, list_t *client)
{
    (void) server;
    (void) client;
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
        manage_client(server, client);
        if (client->size == 2)
            loop_game(server, client);
    }
}
