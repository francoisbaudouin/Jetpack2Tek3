/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** main
*/

#include <stdio.h>
#include "server.h"

int main(char *av, int *ac) 
{
    client_t *client;
    server_t *server;
    
    network_configuration(av[2], server);

    return (0);
}