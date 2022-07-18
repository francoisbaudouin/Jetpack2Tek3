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
    printf("ID\n");
    dprintf(play->socket_fd, "lala\n");
    dprintf(play->socket_fd, "%i", play->id);
}

void map(server_t *server, player_t *play)
{
    printf("test id\n");
}
void ready(server_t *server, player_t *play)
{
    printf("test id");
}
void fire(server_t *server, player_t *play)
{
    printf("test id");
}
void start(server_t *server, player_t *play)
{
    printf("test id");
}
void coin(server_t *server, player_t *play)
{
    printf("test id");
}
void finish(server_t *server, player_t *play)
{
    printf("test id");
}
void player(server_t *server, player_t *play)
{
    printf("test id");
}

static void pars_data(char *str)
{

}

static void exec_player_command(server_t *server, player_t *p,
    char *commands_player) 
{
    command_t commands[] = {
        {"ID\n", id},
        {"MAP\n", map},
        {"READY\n", ready},
        {"FIRE\n", fire},
        {"START\n", start},
        {"PLAYER\n", player},
        {"COIN\n", coin},
        {"FINISH\n", finish},
        {0, NULL},
    };
    for (int i = 0; commands[i].key != 0; i++) {
        printf("%d\n", strcmp(commands_player, commands[i].key));
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
        memset(buffer, '\0', sizeof(buffer));
        if (read(tmp->player->socket_fd, &buffer, sizeof(buffer)) == -1) {
            printf("Server, read error\n");
            return;
        }
        exec_player_command(server, tmp->player, buffer);
        tmp = tmp->next;
    }
}
