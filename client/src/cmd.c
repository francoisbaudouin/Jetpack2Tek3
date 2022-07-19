/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** cmd
*/

#include "../include/client.h"

void id(client_t *client, char **str)
{
    client->id = strdup(str[1]);
    printf("client id: %s\n", client->id);
}

void map(client_t *client, char **str)
{
    int count = size_array(str);

    if (count != 4)
        printf("not enough arguments\n");
    client->actual.width = atoi(str[1]);
    client->actual.height = atoi(str[2]);
    client->actual.map = split_string(client->actual.map, str[3], "\n"); 
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
        {NULL, NULL},
    };

    for (int i = 0; commands[i].key != 0; i++) {
        if (strcmp(str[0], commands[i].key) == 0)
            commands[i].ptr(client, str);
    }
}