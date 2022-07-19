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
    command_t commands[] = {
        {"ID\n", authentication},
        {"MAP\n", map},
        {"READY\n", ready},
        {"FIRE\n", fire},
        {0, NULL},
    };
    for (int i = 0; commands[i].key != 0; i++) {
        if (strcmp(commands_player, commands[i].key) == 0)
            commands[i].ptr(server, p);
    }
}

void read_data_player_command(server_t *server, list_t *client)
{
    //thread
    element_t *tmp = client->first;
    char buffer[255];
    if (tmp == NULL)
        return;
    while (tmp != NULL ) {
        bzero(buffer, sizeof(buffer));
        if (read(tmp->player->socket_fd, &buffer, sizeof(buffer)) == -1) {
            printf("Server, read error\n");
            return;
        }
        printf("buffe: %s : line : %ld\n", buffer, strlen(buffer));
        // FD_ISSET
        exec_player_command(server, tmp->player, buffer);
        tmp = tmp->next;
    }
}
