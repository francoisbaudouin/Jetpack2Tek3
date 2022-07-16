/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** my
*/

#ifndef MY_H_
#define MY_H_

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/System/Time.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

enum state_e {
    WALK,
    JUMP
};

enum entity_e {
    LASER,
    COIN
};

typedef struct player {
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect rect;
    sfVector2f pos;
} player_t;

typedef struct background {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfVector2f scale;
} background_t;

typedef struct obstacle {
    enum entity_e entity;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfVector2f scale;
} obstacle_t;

typedef struct game_object_s{
    enum state_e state;
    struct player Actual;
    struct player Enemy;
    sfClock *clock;
    sfTime time;
    bool alive;
    bool drawable;
}game_object_t;

typedef struct window_s
{
    sfVideoMode mode;
    sfRenderWindow* window;
    sfEvent event;
}window_t;



#endif /* !MY_H_ */
