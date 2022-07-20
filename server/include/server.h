/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

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

#define MAX_CONNECTION 2

typedef struct player_s {
    int socket_fd;
    int id;
    bool connected;
    bool ready;
    size_t score;
    int pos_x;
    int pos_y;
    size_t money;
    bool jetpack;
} player_t;

typedef struct map_s {
    char **map;
    size_t width;
    size_t high;
    char *cells;
} map_t;

typedef struct server_s {
    fd_set rfds;
    fd_set wfds;
    fd_set tmp_rfds;
    fd_set tmp_wfds;
    socklen_t socket_size;
    int socket_fd_server;
    struct sockaddr_in socket_addr;
    map_t *map;
    char *gravity;
    char *port;
    bool server_running;
    char *path_map;
    bool can_strat_game;
} server_t;

typedef struct element_s {
    player_t *player;
    struct element_s *next;
} element_t;

typedef struct list_s {
    element_t *first;
    int size;
} list_t;

/*Check error*/
int check_error_arguments(server_t *server, char **av, int ac);

int network_configuration(server_t *server);

/* MAP MANAGEMENT*/

void load_map(server_t *server, char *path);
bool is_good_character(char *line);

/*init list chain*/
list_t *initialization(void);
list_t *insertion(list_t *list, player_t *player);
list_t *insertion_end(list_t *list, player_t *player);
list_t *delete_first_elem(list_t *list);
list_t *delete_last_elem(list_t *list);

/*read data player*/
void read_data_player_command(server_t *server, list_t *client);

/*Server*/
void running_server(server_t *server);

/*connection client*/
bool new_client_connection(server_t *server, list_t *client);

/*command split string*/
char **split_string(char **str, char *buffer, char *delimiter);

/*move player*/
void move(server_t *server, list_t *client);

#endif /* !SERVER_H_ */
