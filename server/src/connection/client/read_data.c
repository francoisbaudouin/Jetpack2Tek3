/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** read_data
*/

#include "command.h"
#include <string.h>

void id(server_t *server, player_t *play)
{
    dprintf(play->socket_fd, "%i", play->id);
}

void map(server_t *server, player_t *play)
{
    printf("test id\n");
}

void fire(server_t *server, player_t *play, char *data)
{
    if (atoi(data) == 1) {
        play->active_jetpack = true;
        return;
    }
}

void start(server_t *server, player_t *play)
{
    printf("test id");
}

void coin(server_t *server, player_t *play)
{
    printf("test id");
}

/* static void pars_data(char *str)
{

}
 */

static void exec_player_command(server_t *server, player_t *p,
    char *commands_player) 
{
    command_t commands[] = {
        {"ID\n", id},
        {"MAP", map},
        {"FIRE", fire},
        {"START", start},
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
        memset(buffer, 0, 255);
        if (read(tmp->player->socket_fd, &buffer, sizeof(buffer)) == -1) {
            printf("Server, read error\n");
            return;
        }
        printf("%s\n", buffer);
        exec_player_command(server, tmp->player, buffer);
        tmp = tmp->next;
    }
}
