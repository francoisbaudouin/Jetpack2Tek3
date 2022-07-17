/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** server
*/

#include "server.h"

static void manage_client(server_t *server)
{
    list_t *client = initialization();
    if (FD_ISSET(server->socket_fd_server, &server->tmp_rfds)) {
        new_client_connection(server, client);
    }


}

void running_server(server_t *server)
{
    server->server_running = true;
    while (server->server_running == true) {
        server->tmp_rfds = server->rfds;
        server->tmp_wfds = server->wfds;
        if (select(server->socket_fd_server + 1, &server->tmp_rfds, 
            &server->tmp_wfds, NULL, NULL) == -1) {
            perror("select");
            exit(84);
        }
        manage_client(server);
    }
}