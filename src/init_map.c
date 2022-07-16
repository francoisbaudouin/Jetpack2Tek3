/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** init
*/

#include "../my.h"

void init_start(background_t *background)
{
    background->pos.x = 0;
    background->pos.y = 0;
    background->scale.x = 2.7;
    background->scale.y = 2.7;
    background->texture = sfTexture_createFromFile("BackdropEntry.png", NULL);
    background->sprite = sfSprite_create();
    sfSprite_setTexture(background->sprite, background->texture, sfTrue);
    sfSprite_setPosition(background->sprite, background->pos);
    sfSprite_scale(background->sprite, background->scale);
}

void init_background(background_t **background)
{
    for (size_t i = 1; i < 4; i++) {
        background[i] = malloc(sizeof(background_t));
        background[i]->scale.x = 7.0;
        background[i]->scale.y = 2.7;

        background[i]->pos.x = 1400 * i;
        background[i]->pos.y = 25;

        background[i]->texture = sfTexture_createFromFile("BackdropMain.png", NULL);
        background[i]->sprite = sfSprite_create();

        sfSprite_setPosition(background[i]->sprite, background[i]->pos);
        sfSprite_setTexture(background[i]->sprite, background[i]->texture, sfTrue);
        sfSprite_scale(background[i]->sprite, background[i]->scale);
    }
    
}

void init_zap(obstacle_t *obstacle)
{
    obstacle->scale.x = 4.0f;
    obstacle->scale.y = 4.0f;
    obstacle->texture = sfTexture_createFromFile("CoinCollected.png", NULL);
    obstacle->sprite = sfSprite_create();
    obstacle->entity = LASER;
    sfSprite_setTexture(obstacle->sprite, obstacle->texture, sfTrue);
    sfSprite_setPosition(obstacle->sprite, obstacle->pos);
    sfSprite_scale(obstacle->sprite, obstacle->scale);
}

void init_coin(obstacle_t *obstacle)
{
    obstacle->scale.x = 0.1f;
    obstacle->scale.y = 0.1f;
    obstacle->texture = sfTexture_createFromFile("Coin.png", NULL);
    obstacle->sprite = sfSprite_create();
    obstacle->entity = COIN;
    sfSprite_setTexture(obstacle->sprite, obstacle->texture, sfTrue);
    sfSprite_setPosition(obstacle->sprite, obstacle->pos);
    sfSprite_scale(obstacle->sprite, obstacle->scale);
}
