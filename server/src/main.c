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
    if (load_map(server, av) == false)
        return (84);

    if (network_configuration(server) == false)
        return (84);
    free(server);
    return (0);
}