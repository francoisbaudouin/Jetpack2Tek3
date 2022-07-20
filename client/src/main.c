/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** main
*/

#include "../include/client.h"

int check_args(int ac, char **av, client_t *client)
{
    if (ac != 5)
        return (-1);
    for (size_t i = 0; av[i]; i++) {
        if (strcmp(av[i], "-p") == 0 && av[i + 1] != NULL &&
        strcmp(av[i + 1], "-h") != 0) {
            client->port = strdup(av[i + 1]);
            i++;
        }
        if (strcmp(av[i], "-h") == 0 && av[i + 1] != NULL &&
        strcmp(av[i + 1], "-p") != 0) {
            client->ip = strdup(av[i + 1]);
            i++;
        }
    }
    if (!client->port || !client->ip)
        return (-1);
    return (0);
}

int size_array(char **str)
{
    int i = 0;

    for (i = 0; str[i] != NULL; i++);
    return (i);
}

int main(int ac, char **av)
{
    client_t *client = malloc(sizeof(client_t));
    client->ready = false;
    client->fire = false;
    client->start = false;

    if (check_args(ac, av, client) == -1)
        return (84);
    if (init_cli(client) == -1)
        return (84);


    if (pthread_create(&client->thread, NULL, &cli_to_serv,
        (void *)client) != 0) {
            perror("pthread_create() afficher :");
        return (84);
    }
    game(client);
    if (pthread_join(client->thread, NULL) != 0) {
        perror("pthread_join() afficher :");
        return (84);
    }
    return (0);
}
