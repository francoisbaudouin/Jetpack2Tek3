/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** server
*/

#include "server.h"

void running_server(server_t *server)
{
    server->server_running = true;
    while (server->server_running == true) {
        server->tmp_rfds = server->rfds;
        server->tmp_wfds = server->wfds;
        if (select(server->socket_fd_server + 1, &server->tmp_rfds, &server->tmp_wfds, NULL, NULL) == -1) {
            perror("select");
            exit(84);
        }
        for (int i = 0; i <= server->socket_fd_server; i++) {
            if (FD_ISSET(i, &server->tmp_rfds))
                read_client(server, i);
            if (FD_ISSET(i, &server->tmp_wfds))
                write_client(server, i);
        }
    }
}