/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** main
*/

#include "my.h"

char **read_file(char *av, char **buffer)
{
    FILE * fp = fopen(av, "r");
    int y = 0;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1) {
        buffer[y] = malloc(sizeof(char) * strlen(line));
        buffer[y] = strdup(line);
        y++;
    }
    buffer[y] = NULL;
    fclose(fp);
    if (line)
        free(line);
    return (buffer);
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

sfVector2f gravity(sfVector2f actual, game_object_t *game_object)
{
    if (actual.y < 780 && game_object->state == WALK) {
        actual.y += 2;
        game_object->Actual.rect.top = 8;
    }
    sfSprite_setPosition(game_object->Actual.sprite, actual);
    return (actual);
}

float animated_sprite(game_object_t *game_object, sfClock *clock)
{
    if (game_object->Actual.rect.left == 300) {
        game_object->Actual.rect.left = 0;
    } else {
        game_object->Actual.rect.left += 100;
    }
    sfSprite_setTextureRect(game_object->Actual.sprite, game_object->Actual.rect);
    sfClock_restart(clock);
    return (0.0);
}

void init_obstacle(obstacle_t **obstacle, char **buffer)
{
    int x = 500;
    int y = 100;
    int nbr = 0;
    for (size_t i = 0; buffer[i] != NULL; i++) {
        for (size_t j = 0; buffer[i][j]; j++) {
            if (buffer[i][j] == 'e') {
                obstacle[nbr] = malloc(sizeof(obstacle_t) * 1);
                obstacle[nbr]->pos.x = x + j * 90;
                obstacle[nbr]->pos.y = y + i * 90;
                obstacle[nbr]->scale.x = 4.0f;
                obstacle[nbr]->scale.y = 4.0f;
                obstacle[nbr]->texture = sfTexture_createFromFile("CoinCollected.png", NULL);
                obstacle[nbr]->sprite = sfSprite_create();
                obstacle[nbr]->entity = LASER;
                sfSprite_setTexture(obstacle[nbr]->sprite, obstacle[nbr]->texture, sfTrue);
                sfSprite_setPosition(obstacle[nbr]->sprite, obstacle[nbr]->pos);
                sfSprite_scale(obstacle[nbr]->sprite, obstacle[nbr]->scale);
                nbr++;
            }
            if (buffer[i][j] == 'c') {
                obstacle[nbr] = malloc(sizeof(obstacle_t) * 1);
                obstacle[nbr]->pos.x = x + j * 90;
                obstacle[nbr]->pos.y = y + i * 90;
                obstacle[nbr]->scale.x = 0.1f;
                obstacle[nbr]->scale.y = 0.1f;
                obstacle[nbr]->texture = sfTexture_createFromFile("Coin.png", NULL);
                obstacle[nbr]->sprite = sfSprite_create();
                obstacle[nbr]->entity = COIN;
                sfSprite_setTexture(obstacle[nbr]->sprite, obstacle[nbr]->texture, sfTrue);
                sfSprite_setPosition(obstacle[nbr]->sprite, obstacle[nbr]->pos);
                sfSprite_scale(obstacle[nbr]->sprite, obstacle[nbr]->scale);
                nbr++;
            }
        }
    }
    obstacle[nbr] = NULL;
}

void event(window_t *windows, game_object_t *game_object, sfVector2f actual)
{
    while (sfRenderWindow_pollEvent(windows->window, &windows->event))
    {
        if (windows->event.type == sfEvtClosed)
            sfRenderWindow_close(windows->window);
        if (windows->event.type == sfEvtKeyPressed && windows->event.key.code == sfKeySpace && actual.y > 90) {
            game_object->state = JUMP;
        } else if (windows->event.type == sfEvtKeyReleased)
            game_object->state = WALK;
    }
}

void draw_obstacle(window_t *windows, obstacle_t **obstacle)
{
    for (size_t i = 0; obstacle[i]; i++)
    {
        sfRenderWindow_drawSprite(windows->window, obstacle[i]->sprite, NULL);
    }
}

void init_game(game_object_t *game_object, background_t **background, obstacle_t **obstacle, char **buffer)
{
    sfIntRect playerRect = {0, 8, 100, 100};
    sfVector2i playerPos = {100, 540};
    game_object->Actual = init_player(game_object->Actual, playerRect, playerPos);
    game_object->state = WALK;

    background[0] = malloc(sizeof(background_t));
    init_start(background[0]);
    init_obstacle(obstacle, buffer);
}

void jump_player(game_object_t *game_object, sfVector2f actual)
{
    if (game_object->state == JUMP && actual.y > 100) {
        actual.y -= 3;
        game_object->Actual.rect.top = 108;
        sfSprite_setPosition(game_object->Actual.sprite, actual);
    }
}

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

int game(char *av)
{
    char **buffer = malloc(sizeof(char *) * 11);
    float seconds = 0.0;
    window_t *windows = malloc(sizeof(window_t));
    game_object_t *game_object = malloc(sizeof(game_object_t));
    background_t **background = malloc(sizeof(background_t *));
    obstacle_t **obstacle = malloc(sizeof(obstacle_t *) * 100);

    buffer = read_file(av, buffer);
    if (init_window(windows) == -1)
        return (84);
    init_game(game_object, background, obstacle, buffer);

    sfTexture* BackgroundTexture;
    sfSprite *BackgroundSprite;

    sfVector2f BackgroundPos;
    sfVector2f scaleBg;
    scaleBg.x = 7.0;
    scaleBg.y = 2.7;

    BackgroundPos.x = 1400;
    BackgroundPos.y = 25;

    BackgroundTexture = sfTexture_createFromFile("BackdropMain.png", NULL);
    BackgroundSprite = sfSprite_create();

    sfSprite_setPosition(BackgroundSprite, BackgroundPos);
    sfSprite_setTexture(BackgroundSprite, BackgroundTexture, sfTrue);
    sfSprite_scale(BackgroundSprite, scaleBg);

    /* Create a graphical text to display */
    game_object->clock = sfClock_create();

    float second = 0;

    while (sfRenderWindow_isOpen(windows->window))
    {
        sfRenderWindow_clear(windows->window, sfBlack);
        sfVector2f actual = sfSprite_getPosition(game_object->Actual.sprite);
        game_object->time = sfClock_getElapsedTime(game_object->clock);
        seconds = game_object->time.microseconds / 1000000.0;
        actual = gravity(actual, game_object);
        event(windows, game_object, actual);
        if (background[0]->pos.x > -1428) {
            BackgroundPos.x -= 1;
            background[0]->pos.x -= 1;
            sfSprite_setPosition(background[0]->sprite, background[0]->pos);
            sfSprite_setPosition(BackgroundSprite, BackgroundPos);
        }
        jump_player(game_object, actual);
        for (size_t i = 0; obstacle[i]; i++) {
            obstacle[i]->pos.x -= 1;
            sfSprite_setPosition(obstacle[i]->sprite, obstacle[i]->pos);
        }
        if (seconds > 0.2) {
            seconds = animated_sprite(game_object, game_object->clock);
        }
        if (collisions(game_object->Actual, obstacle, windows) == -1) {
            game_object->Actual.rect.top = 324;
        }
        // sfRenderWindow_drawSprite(windows->window, background[0]->sprite, NULL);
        // sfRenderWindow_drawSprite(windows->window, BackgroundSprite, NULL);
        draw_obstacle(windows, obstacle);
        
        sfRenderWindow_drawSprite(windows->window, game_object->Actual.sprite, NULL);
        /* Clear the screen */
        sfRenderWindow_display(windows->window);
    }
    sfRenderWindow_destroy(windows->window);

    return 0;

}

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    else
        game(av[1]);
    return (0);
}