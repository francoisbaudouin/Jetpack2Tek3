/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** main
*/

#include "../include/client.h"

// // sfVector2f gravity(sfVector2f actual, game_object_t *game_object)
// {
//     // if (actual.y < 780 && game_object->state == WALK) {
//         actual.y += 2;
//         // if (game_object->Actual.alive == true)
//             // game_object->Actual.rect.top = 8;
//     }
//     // sfSprite_setPosition(game_object->Actual.sprite, actual);
//     return (actual);
// }

// // // float animated_sprite(game_object_t *game_object, sfClock *clock)
// {
//     // if (game_object->Actual.rect.left == 300) {
//         // game_object->Actual.rect.left = 0;
//     } else {
//         // game_object->Actual.rect.left += 100;
//     }
//     // // sfSprite_setTextureRect(game_object->Actual.sprite, game_object->Actual.rect);
//     sfClock_restart(clock);
//     return (0.0);
// }

void event(window_t *windows, client_t *client)
{
    while (sfRenderWindow_pollEvent(windows->window, &windows->event))
    {
        if (windows->event.type == sfEvtClosed)
            sfRenderWindow_close(windows->window);
        if (windows->event.type == sfEvtKeyPressed && windows->event.key.code == sfKeySpace) {
            client->fire = true;
            // game_object->state = JUMP;

        } else if (windows->event.type == sfEvtKeyReleased)
            client->fire = false;
            // game_object->state = WALK;
    }
}

void draw_obstacle(window_t *windows, obstacle_t **obstacle)
{
    for (size_t i = 0; obstacle[i]; i++)
    {
        if (obstacle[i]->drawable == true)
            sfRenderWindow_drawSprite(windows->window, obstacle[i]->sprite, NULL);
    }
}

// // // void jump_player(game_object_t *game_object, sfVector2f actual)
// {
//     // // if (game_object->state == JUMP && actual.y > 100 && game_object->Actual.alive == true) {
//         actual.y -= 3;
//         // game_object->Actual.rect.top = 108;
//         // sfSprite_setPosition(game_object->Actual.sprite, actual);
//     }
// }

int game(client_t *client)
{
    float seconds = 0.0;
    client->actual_window = malloc(sizeof(window_t));
    // window_t *client->actual_window = malloc(sizeof(window_t));
    // // // game_object_t *game_object = malloc(sizeof(game_object_t));
    // background_t **background = malloc(sizeof(background_t *) * 4);
    // obstacle_t **obstacle = malloc(sizeof(obstacle_t *) * 100);
    float second = 0;

    if (init_window(client->actual_window) == -1)
        return (84);
    // init_game(game_object, background, obstacle, client->actual.map);
    // game_object->clock = sfClock_create();
    // game_object->Actual.alive = true;
    while (sfRenderWindow_isOpen(client->actual_window->window))
    {
        sfRenderWindow_clear(client->actual_window->window, sfBlack);
        //sfVector2f actual = sfSprite_getPosition(game_object->Actual.sprite);
        // // game_object->time = sfClock_getElapsedTime(game_object->clock);
        // seconds = game_object->time.microseconds / 1000000.0;
        // actual = gravity(actual, game_object);
        event(client->actual_window, client);
        // for (size_t i = 0; background[i]; i++) {
        //     if (background[i]->pos.x <= -1990 && i > 0)
        //         background[i]->pos.x = 1250 * 2;
        //     background[i]->pos.x -= 1;
        //     sfSprite_setPosition(background[i]->sprite, background[i]->pos);
        // }
        // jump_player(game_object, actual);
        // for (size_t i = 0; obstacle[i]; i++) {
        //     obstacle[i]->pos.x -= 1;
        //     sfSprite_setPosition(obstacle[i]->sprite, obstacle[i]->pos);
        // }
        // if (seconds > 0.2)
            // // seconds = animated_sprite(game_object, game_object->clock);
        // if (collisions(game_object->Actual, obstacle, client->actual_window == -1)) {
            // game_object->Actual.rect.top = 324;
            // game_object->Actual.alive = false;
        //}
        // sfRenderWindow_drawSprite(client->actual_window.window, background[0]->sprite, NULL);
        // for (size_t i = 0; background[i]; i++)
        //     sfRenderWindow_drawSprite(client->actual_window.window, background[i]->sprite, NULL);
        // draw_obstacle(client->actual_window.obstacle);
        // sfRenderWindow_drawSprite(client->actual_window.window, game_object->Actual.sprite, NULL);
        sfRenderWindow_display(client->actual_window->window);
    }
    sfRenderWindow_destroy(client->actual_window->window);
    return 0;
}
