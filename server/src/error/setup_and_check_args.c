/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** error
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>

static void message_not_enough_arguments(void)
{
    printf("USAGE:\n");
    printf("\t./serverJ2T3 [-p <port> |-g <gravity> | -m <map>]\n");
}

static void arguments_value(server_t *server, char **av)
{
   for (size_t i = 0; av[i]; i++)
    {
        if (strcmp(av[i], "-p") == 0 && av[i + 1] != NULL) {
            server->port = strdup(av[i + 1]);
            i++;
        }
        if (strcmp(av[i], "-g") == 0 && av[i + 1] != NULL) {
            server->gravity = strdup(av[i + 1]);
            i++;
        }
        if (strcmp(av[i], "-m") == 0 && av[i + 1] != NULL) {
            server->path_map = strdup(av[i + 1]);
            i++;
        }
    }
}

int check_error_arguments(server_t *server, char **av, int ac)
{
    if (ac != 7) {
        printf("not enough arguments\n");
        message_not_enough_arguments();
        return (-1);
    }
    arguments_value(server, av);
    if (server->gravity == NULL || server->port == NULL ||
        server->path_map == NULL)
        return (-1); 
    return (0);
}
