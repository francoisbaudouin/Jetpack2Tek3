/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** network
*/

#include "server.h"

static bool checkup_configuration(server_t *server)
{
    if (server->socket_fd_server == -1) {
        printf("socket connexion failed\n");
        close(server->socket_fd_server);
        return (false);
    }
    if (bind(server->socket_fd_server, (struct sockaddr *) &server->socket_addr, 
        sizeof(server->socket_addr)) != 0) {
        printf("Error bind");
        close(server->socket_fd_server);
        return (false);
    }
    return (true);
}

server_t *network_configuration(server_t *server)
{
    FD_ZERO(&server->rfds);
    FD_ZERO(&server->wfds);
    FD_ZERO(&server->tmp_rfds);
    FD_ZERO(&server->tmp_wfds);
    server->socket_fd_server = socket(AF_INET, SOCK_STREAM,
        getprotobyname("tcp")->p_proto);
    server->socket_addr.sin_family = AF_INET;
    server->socket_addr.sin_port = htons(server->port);
    server->socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (checkup_configuration(server) == false)
        return (NULL);
    server->socket_size = sizeof(struct sockaddr);
    bzero(&server->socket_addr, sizeof(server->socket_addr));
    FD_SET(server->socket_fd_server, &server->rfds);
    listen(server->socket_fd_server, MAX_CONNECTION);
    return (server);
}
