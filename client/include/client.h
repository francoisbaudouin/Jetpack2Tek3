/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <netinet/in.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdint.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <pthread.h>
    #include "stdbool.h"
    #include <unistd.h>
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

typedef struct function_ptrs {
    char *key;
    void (*ptr)();
} function_ptr_t;

typedef struct player_s {
    char **map;
    int id;
    int width;
    int height;
    int cells;
    float x;
    float y;
    bool fire;
    int score;
} player_t;

typedef struct window_s
{
    sfVideoMode mode;
    sfRenderWindow* window;
    sfEvent event;
}window_t;

typedef struct client_s {
    sfText *text;
    sfFont *font;
    sfVector2f pos_text;
    char *port;
    char *ip;
    char *id;
    int fd;
    struct sockaddr_in servaddr;
    fd_set rfds;
    pthread_t thread;
    struct player_s actual;
    struct player_s enemy;
    struct window_s *actual_window;
    bool ready;
    bool fire;
    bool start;
    fd_set wfds;
} client_t;

enum state_e {
    WALK,
    JUMP
};

enum entity_e {
    LASER,
    COIN
};

typedef struct background {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfVector2f scale;
} background_t;

char **split_string(char **str, char *buffer, char *delimiter);
char **split_string_map(char **str, char *buffer, client_t *client);
int count_space(char *str, char delim);
void exec_player_command(client_t *client, char **str);
void fire(client_t *client, char **str);
void ready(client_t *client, char **str);
void map(client_t *client, char **str);
void id(client_t *client, char **str);
void *cli_to_serv(void *client);
void reply_from_serv(client_t *client, fd_set wfds, fd_set rfds);
void get_answer(client_t *client);
int init_cli(client_t *client);
int size_array(char **str);
int game(client_t *client);
int init_window(window_t *windows);

#endif /* !CLIENT_H_ */
