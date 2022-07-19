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
        {"ID", id},
        {"MAP", map},
        {"READY", ready},
        {"FIRE", fire},
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
    //dprintf(client->first->player->socket_fd, "\n");
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
        int i = 0;
        for (; buffer[i] != '\0' && buffer[i] != '\r'; i++);
        buffer[i-1] = '\0';
        printf("buffer: %s: Len : %li\n ", buffer, strlen(buffer));
        exec_player_command(server, tmp->player, buffer);
        tmp = tmp->next;
    }
}
