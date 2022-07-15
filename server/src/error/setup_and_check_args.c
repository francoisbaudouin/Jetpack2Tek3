/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** error
*/

#include "server.h"
#include <string.h>
#include <stdlib.h>

static bool check_port_argument(server_t *server, char **argv)
{
    int port = 0; 
    if (strcmp(argv[1], "-p") != 0 || (port = atoi(argv[2])) == 0)
        return (false);
    server->port = port;
    return (true);
}

static bool check_gravity_argument(server_t *server, char **argv)
{
    int gravity = 0; 
    if (strcmp(argv[3], "-g") != 0 || (gravity = atoi(argv[4])) == 0)
        return (false);
    server->gravity = gravity;
    return (true);
}

bool check_error_arguments(server_t *server, char **av)
{
    if (check_port_argument(server, av) == false
        || check_gravity_argument(server, av) == false)
        return (false);
    return (true);
}