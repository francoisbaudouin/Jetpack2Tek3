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

void id(client_t *client, char **str)
{
    dprintf(client->fd, "ID\n");
}

int size_array(char **str)
{
    int i = 0;
    for (i = 0; str[i] != NULL; i++);
    return (i);
}

void map(client_t *client, char **str)
{
    int count = size_array(str);
    if (count != 4)
        printf("pas asser d'arguments\n");
    client->actual.width = atoi(str[1]);
    client->actual.height = atoi(str[2]);
    printf("%d\n", client->actual.width);
    printf("%d\n", client->actual.height);
    client->actual.map = split_string(client->actual.map, str[3], "\n"); 
}

void ready(client_t *client, char **str)
{
    int count = size_array(str);
    if (count != 1)
        printf("pas asser d'arguments\n");
    client->ready = true;
}

void fire(client_t *client, char **str)
{
    int count = size_array(str);
    if (count != 2)
        printf("pas asser d'arguments\n");
    client->fire = true;
}

static void exec_player_command(client_t *client, char **str)
{
    function_ptr_t commands[] = {
        {"ID", id},
        {"MAP", map},
        {"READY", ready},
        {"FIRE", fire},
        {NULL, NULL},
    };
    for (int i = 0; commands[i].key != 0; i++) {
        if (strcmp(str[0], commands[i].key) == 0)
            commands[i].ptr(client, str);
    }
}

void get_answer(client_t *client)
{
    char *buff = calloc(sizeof(char), 1000);
    size_t size;
    FILE *stream = fdopen(client->fd, "r");

    if (!stream)
        return;
    if (getline(&buff, &size, stream) == -1)
        return;
}

void send_id(client_t *client)
{
    printf("a\n");
    send(client->fd, "ID\n", 3, 0);
    dprintf(client->fd, "ID\n");
}

void reply_from_serv(client_t *client, fd_set copy_rd)
{
    for (int fds = 0; fds < FD_SETSIZE; fds++) {
        if (FD_ISSET(fds, &copy_rd)) {
            printf("a\n");
            dprintf(fds, "ID\n");
            send_id(client);
        }
    }
    // if (FD_ISSET(client->fd, &client->rfds))
    //     get_answer(client);
}

int cli_to_serv(client_t *client)
{
    fd_set copy_rd;
    FD_SET(client->fd, &client->rfds);
    while (1) {
        copy_rd = client->rfds;
        if (select(FD_SETSIZE, &copy_rd, NULL, NULL, NULL) == -1) {
            return (-1);
        } else {
            reply_from_serv(client, copy_rd);
        }
    }
    return (0);
}

int main(int ac, char **av) 
{
    client_t *client = malloc(sizeof(client_t));
    client->ready = false;
    client->fire = false;
    client->start = false;
    client->fd = 0;
    if (check_args(ac, av, client) == -1)
        return (84);
    if (init_cli(client) == -1)
        return (84);
    cli_to_serv(client);
    return 0;
}