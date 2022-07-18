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
#include <pthread.h>
#include "stdbool.h"

typedef struct client_s
{
    char *port;
    char *ip;
    int fd;
    struct sockaddr_in servaddr;
    fd_set rfds;
    pthread_t *thread;
} client_t;

typedef struct player_s
{
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



#endif /* !CLIENT_H_ */
