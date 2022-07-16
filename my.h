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
    bool alive;
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
    bool drawable;
} obstacle_t;

typedef struct game_object_s{
    enum state_e state;
    struct player Actual;
    struct player Enemy;
    sfClock *clock;
    sfTime time;
}game_object_t;

typedef struct window_s
{
    sfVideoMode mode;
    sfRenderWindow* window;
    sfEvent event;
}window_t;

int game(char *av);
void jump_player(game_object_t *game_object, sfVector2f actual);
void init_game(game_object_t *game_object, background_t **background, obstacle_t **obstacle, char **buffer);
void draw_obstacle(window_t *windows, obstacle_t **obstacle);
void event(window_t *windows, game_object_t *game_object, sfVector2f actual);
float animated_sprite(game_object_t *game_object, sfClock *clock);
sfVector2f gravity(sfVector2f actual, game_object_t *game_object);
char **read_file(char *av, char **buffer);

void init_coin(obstacle_t *obstacle);
void init_zap(obstacle_t *obstacle);
void init_background(background_t **background);
void init_start(background_t *background);

void check_obstacle(obstacle_t **obstacle, int nbr, int i, int j);
int check_type_obstacle(obstacle_t **obstacle, char **buffer, int i, int nbr);
void init_obstacle(obstacle_t **obstacle, char **buffer);
int init_window(window_t *windows);
player_t init_player(player_t player, sfIntRect playerRect, sfVector2i playerPos);

#endif /* !MY_H_ */
