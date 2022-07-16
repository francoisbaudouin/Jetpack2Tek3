/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** collision
*/

#include "../my.h"

int collisions(player_t player, obstacle_t **obstacle, window_t *windows)
{
    sfRectangleShape *rectangle;
    sfRectangleShape *rectangle2;

    rectangle = sfRectangleShape_create();
    sfVector2f pos1a = sfSprite_getPosition(player.sprite);
    sfVector2f pos2a = pos1a;
    sfVector2f size1 = {100, 100};
    int i = 0;
    pos2a.x = 95;
    pos2a.y -= 5;
    sfRectangleShape_setPosition(rectangle, pos2a);
    sfRectangleShape_setSize(rectangle, size1);
    sfRectangleShape_setFillColor(rectangle, sfRed);
    sfRenderWindow_drawRectangleShape(windows->window, rectangle, NULL);
    while (obstacle[i]){
        rectangle2 = sfRectangleShape_create();
        sfVector2f pos1b = sfSprite_getPosition(obstacle[i]->sprite);
        sfVector2f pos2b = pos1b;
        sfVector2f size2 = {50, 60};

        sfRectangleShape_setPosition(rectangle2, pos2b);
        sfRectangleShape_setSize(rectangle2, size2);
        sfRectangleShape_setFillColor(rectangle2, sfBlue);
        sfRenderWindow_drawRectangleShape(windows->window, rectangle2, NULL);
        if (pos2a.x < pos2b.x + size2.x &&
            pos2a.x + size1.x > pos2b.x &&
            pos2a.y < pos2b.y + size2.y &&
            size1.y + pos2a.y > pos2b.y && obstacle[i]->entity == LASER)
            return (-1);
        i++;
    }
    return (0);
}