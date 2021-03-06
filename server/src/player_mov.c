/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** player_mov
*/

#include "server.h"

static void gravity_move(server_t *server, element_t *player)
{
    int gravity = atoi(server->gravity);
    if (player->player->pos_y <= 0 && player->player->jetpack == false) {
        player->player->pos_y += 1 * gravity;
        printf("play pos: %d\n", player->player->pos_x);
    }
    if (player->player->pos_y >= 70 && player->player->jetpack == true) {
        player->player->pos_y -= 1 * gravity;
    }
}

void move(server_t *server, list_t *client)
{
    element_t *tmp = client->first;

    while (tmp != NULL)
    {
        gravity_move(server, tmp);
        printf("pos: %d\n", tmp->player->pos_x);
        
        tmp = tmp->next;
    }
}