/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** read_data
*/

#include "server.h"

static void pars_data(char *str)
{

}

void read_data_player_command(server_t *server, list_t *client)
{
    //thread
    element_t *tmp;
    char *buffer[255];

    while ( tmp != NULL ) {
        if (read(tmp->player->socket_fd, &buffer, sizeof(buffer)) == -1) {
            printf("Server, read error\n");
            return;
        }
        if (tmp->player->ready == true)
        return;
        tmp = tmp->next;
    }
}
