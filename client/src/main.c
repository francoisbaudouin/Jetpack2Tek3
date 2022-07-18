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
}

int server_connexion(client_t *client, char *ip, char *port)
{
    if (connect(client->fd, (struct sockaddr *)&client->servaddr,
    sizeof(client->servaddr)) != 0) {
        return (-1);
    } else {
        dprintf(1, "connected to %s port %s", ip, port);
    }
    return 0;
}

int init_cli(client_t *client)
{
    uint32_t uint_ip = htonl(atoi(client->ip));
    int int_port = atoi(client->port);

    client->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!client->fd)
        return (-1);
    bzero(&client->servaddr, sizeof(client->servaddr));
    if (uint_ip <= 0 || int_port <= 0)
        return -1;
    client->servaddr.sin_family = AF_INET;
    client->servaddr.sin_addr.s_addr = inet_addr(client->ip);
    client->servaddr.sin_port = htons(int_port);
    if (connect_to_server(client, client->ip, client->port) == -1)
        return -1;
    FD_ZERO(&client->rfds);
}

void get_answer(client_t *client)
{
    char *buff = calloc(sizeof(char), 1000);
    size_t size;
    FILE *stream = fdopen(client->fd, "r");

    if (!stream) {
        perror("fdopen()");
        return;
    }
    if (getline(&buff, &size, stream) == -1)
        return;
    printf("%s\n", buff);
}

void reply_from_serv(client_t *client)
{
    if (FD_ISSET(client->fd, &client->rfds))
        get_answer(client);
}

int cli_to_serv(client_t *client)
{
    while (1) {
        FD_SET(client->fd, &client->rfds);
        if (select(FD_SETSIZE, &client->rfds, NULL, NULL, NULL) == -1) {
            reply_from_serv(client);
        } else
            return (-1);
    }
}

int main(int ac, char **av) 
{
    client_t *client = malloc(sizeof(client));

    if (check_args(ac, av, client) == -1)
        return (84);
    if (init_cli(client) == -1)
        return (84);
    if (pthread_create(&client->thread, NULL, &cli_to_serv, client) != 0) {
        perror("pthread_create() afficher :");
        return (84);
    }
    if (pthread_join(client->thread, NULL) != 0) {
        perror("pthread_join() afficher :");
        return (84);
    }
    return 84;
}