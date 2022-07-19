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

typedef struct function_ptrs {
    char *key;
    void (*ptr)();
} function_ptr_t;

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

typedef struct client_s
{
    char *port;
    char *ip;
    char *id;
    int fd;
    struct sockaddr_in servaddr;
    fd_set rfds;
    pthread_t *thread;
    struct player_s actual;
    bool ready;
    bool fire;
    bool start;
} client_t;

char **split_string(char **str, char *buffer, char *delimiter);
int count_space(char *str, char delim);
void exec_player_command(client_t *client, char **str);
void fire(client_t *client, char **str);
void ready(client_t *client, char **str);
void map(client_t *client, char **str);
void id(client_t *client, char **str);
int cli_to_serv(client_t *client);
void reply_from_serv(client_t *client, fd_set wfds, fd_set rfds);
void get_answer(client_t *client);
int init_cli(client_t *client);
int size_array(char **str);

#endif /* !CLIENT_H_ */
