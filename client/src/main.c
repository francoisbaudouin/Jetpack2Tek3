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

void init_player(player_t player)
{
    player.x = 0;
    player.y = 0;
    player.cells = 0;
    player.fire = false;
    player.height = 0;
    player.width = 0;
    player.id = 0;
    player.map = NULL;
    player.score = 0;
}

void init_struct(client_t *client)
{
    init_player(client->actual);
    init_player(client->enemy);
    client->ip = NULL;
    client->id = NULL;
    client->fd = 0;
    client->port = NULL;
    client->ready = false;
    client->fire = false;
    client->start = false;
    client->id = NULL;
    client->actual.map = NULL;
}

int main(int ac, char **av)
{
    client_t *client = malloc(sizeof(client_t));
    client->actual_window = malloc(sizeof(window_t));
    init_struct(client);
    pthread_t t;

    if (check_args(ac, av, client) == -1)
        return (84);
    if (init_cli(client) == -1)
        return (84);
    if (pthread_create(&t, NULL, cli_to_serv,
        (void *)client) != 0) {
            perror("pthread_create() afficher :");
        return (84);
    }
    game(client);
    if (pthread_join(t, NULL) != 0) {
        perror("pthread_join() afficher :");
        return (84);
    }
    return (0);
}
