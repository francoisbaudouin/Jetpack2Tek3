/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** init_game
*/

#include "../my.h"

void check_obstacle(obstacle_t **obstacle, int nbr, int i, int j)
{
    int x = 500;
    int y = 100;

    obstacle[nbr] = malloc(sizeof(obstacle_t) * 1);
    obstacle[nbr]->pos.x = x + j * 90;
    obstacle[nbr]->pos.y = y + i * 90;
}

int check_type_obstacle(obstacle_t **obstacle, char **buffer, int i, int nbr)
{
    for (size_t j = 0; buffer[i][j]; j++) {
        if (buffer[i][j] == 'e') {
            check_obstacle(obstacle, nbr, i, j);
            init_zap(obstacle[nbr]);
            nbr++;
        }
        if (buffer[i][j] == 'c') {
            check_obstacle(obstacle, nbr, i, j);
            init_coin(obstacle[nbr]);
            nbr++;
        }
    }
    return (nbr);
}

void init_obstacle(obstacle_t **obstacle, char **buffer)
{
    int x = 500;
    int y = 100;
    int nbr = 0;
    for (size_t i = 0; buffer[i] != NULL; i++) {
        nbr = check_type_obstacle(obstacle, buffer, i, nbr);
    }
    obstacle[nbr] = NULL;
}

int init_window(window_t *windows)
{
    windows->mode.bitsPerPixel = 32;
    windows->mode.width = 1920;
    windows->mode.height = 1080;
    windows->window = sfRenderWindow_create(windows->mode, "SFML window", sfResize | sfClose, NULL);
    if (!windows->window)
        return (-1);
    return (0);
}

player_t init_player(player_t player, sfIntRect playerRect, sfVector2i playerPos)
{
    player.rect.top = playerRect.top;
    player.rect.left = playerRect.left;
    player.rect.width = playerRect.width;
    player.rect.height = playerRect.height;
    player.pos.x = playerPos.x;
    player.pos.y = playerPos.y;
    player.texture = sfTexture_createFromFile("barry.png", NULL);
    player.sprite = sfSprite_create();
    sfSprite_setTexture(player.sprite, player.texture, sfTrue);
    sfSprite_setTextureRect(player.sprite, player.rect);
    sfSprite_setPosition(player.sprite, player.pos);
    return (player);
}