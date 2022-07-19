/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** cli_to_serv
*/

#include "../include/client.h"

void get_answer(client_t *client)
{
    char *buff = calloc(sizeof(char), 1000);
    size_t size;
    char **str = NULL;
    FILE *stream = fdopen(client->fd, "r");

    if (!stream)
        return;
    if (getline(&buff, &size, stream) == -1)
        return;
    str = split_string(str, buff, " ");
    exec_player_command(client, str);

    printf("buffer from server: %s\n", buff);
}

void reply_from_serv(client_t *client, fd_set wfds, fd_set rfds, int *nb)
{
    if (FD_ISSET(client->fd, &wfds) && client->id == NULL) {
        dprintf(client->fd, "ID\n");
    }
    if (FD_ISSET(client->fd, &rfds))
        get_answer(client);
}

int cli_to_serv(client_t *client)
{
    fd_set wfds;
    fd_set wfds_tmp;
    fd_set rfds_tmp;
    FD_ZERO(&rfds_tmp);
    FD_ZERO(&wfds_tmp);
    FD_ZERO(&wfds);
    FD_SET(client->fd, &wfds);
    FD_SET(client->fd, &client->rfds);
    int nb = 0;

    while (1) {
        rfds_tmp = client->rfds;
        wfds_tmp = wfds;
        if (select(FD_SETSIZE, &rfds_tmp, &wfds_tmp, NULL, NULL) == -1) {
            perror("select()");
            return (-1);
        } else {
            reply_from_serv(client, wfds_tmp, rfds_tmp, &nb);
        }
    }
    return (0);
}