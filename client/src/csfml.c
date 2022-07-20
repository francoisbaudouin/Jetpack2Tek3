/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** main
*/

#include "../include/client.h"

void event(window_t *windows, client_t *client)
{
    while (sfRenderWindow_pollEvent(windows->window, &windows->event)) {
        if (windows->event.type == sfEvtClosed)
            sfRenderWindow_close(windows->window);
        if (windows->event.type == sfEvtKeyPressed &&
            windows->event.key.code == sfKeySpace)
            client->fire = true;
        else if (windows->event.type == sfEvtKeyReleased)
            client->fire = false;
    }
}

void parallax(background_t **background)
{
    for (size_t i = 0; background[i]; i++) {
        if (background[i]->pos.x <= -2000 && i > 0)
            background[i]->pos.x = 1000 * 2;
        background[i]->pos.x -= 1;
        sfSprite_setPosition(background[i]->sprite, background[i]->pos);
    }
}

void destroy(client_t *client)
{
    sfText_destroy(client->text);
    sfFont_destroy(client->font);
    sfRenderWindow_destroy(client->actual_window->window);
}

void draw(background_t **background, client_t *client)
{
    for (size_t i = 0; background[i]; i++)
        sfRenderWindow_drawSprite(client->actual_window->window,
    background[i]->sprite, NULL);
    sfRenderWindow_drawText(client->actual_window->window, client->text, NULL);
}

int game(client_t *client)
{
    float seconds = 0.0;
    background_t **background = malloc(sizeof(background_t *) * 4);
    client->font = sfFont_createFromFile("arial.ttf");
    float second = 0;

    if (init_window(client->actual_window) == -1)
        return (84);
    init_background(background);
    init_txt(client);
    while (sfRenderWindow_isOpen(client->actual_window->window)) {
        sfRenderWindow_clear(client->actual_window->window, sfBlack);
        event(client->actual_window, client);
        parallax(background);
        draw(background, client);
        sfRenderWindow_display(client->actual_window->window);
    }
    destroy(client);
    return 0;
}
