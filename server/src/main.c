/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** main
*/

#include <stdio.h>
#include "server.h"


static void message_not_enough_arguments(void)
{
    printf("USAGE:\n");
    printf("\t./serverJ2T3 [-p <port> |-g <gravity> | -m <map>]\n");
}

int main(int ac, char **av) 
{
    client_t *client;
    server_t *server = malloc(sizeof(server_t));
    (void) client;
    
    if (ac != 7) {
        printf("not enough arguments\n");
        message_not_enough_arguments();
        return (84);
    }

    server = check_error_arguments(server, av);
    if (server == false) {
        printf("error arguments\n");
        return (84);
    }

    printf("My port %d", server->port);
    server = load_map(server, av);
    if (server == NULL)
        return (84);
    server = network_configuration(server);
    if ( server == false)
        return (84);

    running_server(server);
    free(server);
    return (0);
}