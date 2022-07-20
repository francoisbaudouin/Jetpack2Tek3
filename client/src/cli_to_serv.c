/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** cli_to_serv
*/

#include "../include/client.h"

void get_answer(client_t *client)
{
    //char *buff = calloc(sizeof(char), 1000);
    char buff[1024];
    size_t size;
    char **str = NULL;
    FILE *stream = fdopen(client->fd, "r");

    if (!stream)
        return;
    read(client->fd, &buff, sizeof(buff));
    str = split_string(str, buff, " ");
    exec_player_command(client, str);
}

void reply_from_serv(client_t *client, fd_set wfds, fd_set rfds)
{
    if (FD_ISSET(client->fd, &wfds) && client->id == NULL) {
        dprintf(client->fd, "ID\n");
    }
    if (FD_ISSET(client->fd, &wfds) && client->actual.map == NULL && client->id != NULL) {
        dprintf(client->fd, "MAP\n");
    }
    if (FD_ISSET(client->fd, &wfds) && client->actual.map != NULL && client->id != NULL && client->ready == false) {
        client->ready = true;
        dprintf(client->fd, "READY\n");
    }
    if (FD_ISSET(client->fd, &wfds) && client->fire == true) {
        dprintf(client->fd, "FIRE 1\n");
    } else if (FD_ISSET(client->fd, &wfds) && client->fire == false) {
        dprintf(client->fd, "FIRE 0\n");
    }
    if (FD_ISSET(client->fd, &rfds))
        get_answer(client);
}

int cli_to_serv(client_t *client)
{
    fd_set wfds_tmp;
    fd_set rfds_tmp;
    FD_ZERO(&rfds_tmp);
    FD_ZERO(&wfds_tmp);
    FD_SET(client->fd, &client->wfds);
    FD_SET(client->fd, &client->rfds);

    while (1) {
        rfds_tmp = client->rfds;
        wfds_tmp = client->wfds;
        if (select(FD_SETSIZE, &rfds_tmp, &wfds_tmp, NULL, NULL) == -1) {
            perror("select()");
            return (-1);
        } else {
            reply_from_serv(client, wfds_tmp, rfds_tmp);
        }
        game(client);
    }
    return (0);
}
