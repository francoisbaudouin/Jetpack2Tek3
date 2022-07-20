/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** cmd
*/

#include "../include/client.h"

void player(client_t *client, char **str)
{
    if (strcmp(client->id, str[1]) == 0) {
        client->actual.x = atof(str[2]);
        client->actual.y = atof(str[3]);
        client->actual.score = atof(str[4]);
    } else {
        client->enemy.x = atof(str[2]);
        client->enemy.y = atof(str[3]);
        client->enemy.score = atof(str[4]);
    }
}

void id(client_t *client, char **str)
{
    client->id = strdup(str[1]);
    printf("client id: %s\n", client->id);
}

void map(client_t *client, char **str)
{
    // int count = size_array(str);

    // if (count != 4)
    //     printf("not enough arguments\n");
    client->actual.width = atoi(str[1]);
    client->actual.height = atoi(str[2]);
    client->actual.map = malloc(sizeof(char *) * (client->actual.height));
    for (size_t i = 0; i < client->actual.height; i++)
        client->actual.map[i] = malloc(sizeof(char) * client->actual.width + 1);
    client->actual.map = split_string_map(client->actual.map, str[3], client);
}

void ready(client_t *client, char **str)
{
    int count = size_array(str);

    if (count != 1)
        printf("not enough arguments\n");
    client->ready = true;
}

void fire(client_t *client, char **str)
{
    int count = size_array(str);

    if (count != 2)
        printf("not enough arguments\n");
    client->fire = true;
}

void exec_player_command(client_t *client, char **str)
{
    function_ptr_t commands[] = {
        {"ID", id},
        {"MAP", map},
        {"READY", ready},
        {"FIRE", fire},
        {"PLAYER", player},
        {NULL, NULL},
    };

    for (int i = 0; commands[i].key != 0; i++) {
        if (strcmp(str[0], commands[i].key) == 0)
            commands[i].ptr(client, str);
    }
}
