/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#define MAX_CONNECTION 2

#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdbool.h>


typedef struct player_s {
    int socket_fd;
    int id;
    bool connected;
    bool ready;
    size_t pos_x;
    size_t pos_y;
} player_t;

typedef struct client_s {
    player_t p1;
    player_t p2;
    int nb_player;
} client_t;

typedef struct server_s {
    fd_set rfds;
    fd_set wfds;
    fd_set tmp_rfds;
    fd_set tmp_wfds;
    int socket_fd_server;
    struct sockaddr_in socket_addr;
    /* data */
} server_t;


#endif /* !SERVER_H_ */