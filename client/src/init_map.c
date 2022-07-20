/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** init
*/

#include "../include/client.h"

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
    for (size_t i = 0; i < 4; i++) {
        background[i] = malloc(sizeof(background_t));
        background[i]->scale.x = 7.0;
        background[i]->scale.y = 3.0;
        background[i]->pos.x = 1200 * i;
        background[i]->pos.y = 0;
        background[i]->texture = sfTexture_createFromFile("BackdropMain.png", NULL);
        background[i]->sprite = sfSprite_create();
        sfSprite_setPosition(background[i]->sprite, background[i]->pos);
        sfSprite_setTexture(background[i]->sprite, background[i]->texture, sfTrue);
        sfSprite_scale(background[i]->sprite, background[i]->scale);
    }
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

void init_txt(client_t *client)
{
    client->pos_text.x = 20;
    client->pos_text.y = 20;
    client->text = sfText_create();
    sfText_setString(client->text, "Piece");
    sfText_setFont(client->text, client->font);
    sfText_setCharacterSize(client->text, 50);
    sfText_setPosition(client->text, client->pos_text);
}
