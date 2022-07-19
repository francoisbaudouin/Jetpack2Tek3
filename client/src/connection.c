/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** connexion
*/

#include "../include/client.h"

int server_connexion(client_t *client, char *ip, char *port)
{
    if (connect(client->fd, (struct sockaddr *)&client->servaddr,
    sizeof(client->servaddr)) == -1) {
        return (-1);
    } else {
        dprintf(1, "connected to %s port %s\n", ip, port);
        return (0);
    }
    return 0;
}

int init_cli(client_t *client)
{
    uint32_t ip = htonl(atoi(client->ip));
    int port = atoi(client->port);

    client->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!client->fd)
        return (-1);
    bzero(&client->servaddr, sizeof(client->servaddr));
    if (ip <= 0 || port <= 0)
        return (-1);
    client->servaddr.sin_family = AF_INET;
    client->servaddr.sin_addr.s_addr = inet_addr(client->ip);
    client->servaddr.sin_port = htons(port);
    if (server_connexion(client, client->ip, client->port) == -1)
        return (-1);
    FD_ZERO(&client->rfds);
    FD_ZERO(&client->wfds);
    return (0);
}
