/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** server
*/

#include "server.h"
#include <signal.h>

static void manage_client(server_t *server)
{
    list_t *client = initialization();
    element_t *tmp;
    if (FD_ISSET(server->socket_fd_server, &server->tmp_rfds)) {
        printf("newplayer\n");
        new_client_connection(server, client);
    } else {
        printf("readdata\n");
        read_data_player_command(server, client);
    }
}

void running_server(server_t *server)
{
    //signal(SIGINT, (__sighandler_t)(server->server_running = false));
    server->server_running = true;
    while (server->server_running == true) {
        server->tmp_rfds = server->rfds;
        server->tmp_wfds = server->wfds;
        if (select(server->socket_fd_server + 1, &server->tmp_rfds, 
            &server->tmp_wfds, NULL, NULL) == -1) {
            perror("select");
            return;
        }
        manage_client(server);
    }
}