/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** read_data
*/

#include "command.h"
#include <string.h>
#include <ctype.h>

static void exec_player_command(server_t *server, player_t *p,
    char *commands_player) 
{
    char **str_command = NULL;
    command_t commands[] = {
        {"ID\n", authentication},
        {"MAP\n", map},
        {"READY\n", ready},
        {"FIRE\n", fire},
        {0, NULL},
    };
    str_command = split_string(str_command, commands_player, " ");
    for (int i = 0; commands[i].key != 0; i++) {
        if (strcmp(str_command[0], commands[i].key) == 0)
            commands[i].ptr(server, p, str_command);
    }
}

static void player_send_data(server_t *server, list_t *client)
{
    element_t *p1;

    p1 = client->first;
    if (p1->player->ready)
        dprintf(p1->player->socket_fd, "PLAYER %d %d %d %ld\n", p1->player->id, 
            p1->player->pos_x, p1->player->pos_x, p1->player->score);
}

void read_data_player_command(server_t *server, list_t *client)
{
    element_t *tmp = client->first;
    char buffer[255];
    if (tmp == NULL)
        return;
    while (tmp != NULL) {
        bzero(buffer, sizeof(buffer));
        if (read(tmp->player->socket_fd, &buffer, sizeof(buffer)) == -1) {
            printf("Server, read error\n");
            return;
        }
        if (FD_ISSET(tmp->player->socket_fd, &server->tmp_rfds))
            exec_player_command(server, tmp->player, buffer);
        if (FD_ISSET(tmp->player->socket_fd, &server->tmp_wfds))
            player_send_data(server, client);
        tmp = tmp->next;
    }
}
