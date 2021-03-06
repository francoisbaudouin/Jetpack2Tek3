/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** cli_to_serv
*/

#include "../include/client.h"

void get_answer(client_t *client)
{
    char buff[1024];
    char **str = NULL;

    if (!read(client->fd, &buff, sizeof(buff)))
        return;
    if (buff != NULL) {
        str = split_string(str, buff, " ");
        exec_player_command(client, str);
    }
}

void fire_cmd(client_t *client, fd_set wfds)
{
    if (FD_ISSET(client->fd, &wfds) && client->fire == true) {
        dprintf(client->fd, "FIRE 1\n");
    } else if (FD_ISSET(client->fd, &wfds) && client->fire == false) {
        dprintf(client->fd, "FIRE 0\n");
    }
}

void server_to_cli(client_t *client, fd_set wfds)
{
    if (FD_ISSET(client->fd, &wfds) && client->id == NULL) {
        dprintf(client->fd, "ID\n");
    }
    if (FD_ISSET(client->fd, &wfds) && client->actual.map == NULL 
        && client->id != NULL) {
        dprintf(client->fd, "MAP\n");
    }
    if (FD_ISSET(client->fd, &wfds) && client->actual.map != NULL 
        && client->id != NULL && client->ready == false) {
        client->ready = true;
        dprintf(client->fd, "READY\n");
    }
    fire_cmd(client, wfds);
}

void reply_from_serv(client_t *client, fd_set wfds, fd_set rfds)
{
    server_to_cli(client, wfds);
    if (FD_ISSET(client->fd, &rfds))
        get_answer(client);
}

void *cli_to_serv(void * av)
{
    client_t *client = (client_t*)av;
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
            return (NULL);
        } else {
            reply_from_serv(client, wfds_tmp, rfds_tmp);
        }
    }
    pthread_exit(NULL);
}
