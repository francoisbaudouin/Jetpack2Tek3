/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** main
*/

#include <stdio.h>
#include "server.h"

int main(int ac, char **av) 
{
    server_t *server = malloc(sizeof(server_t));

    if (check_error_arguments(server, av, ac) == -1)
        return (84);
    load_map(server, server->path_map);
    for (size_t i = 0; server->map->map[i]; i++)
    {
        printf("%s\n", server->map->map[i]);
    }
    if (network_configuration(server) == -1)
        return (84);
    running_server(server);
    free(server);
    return (0);
}
