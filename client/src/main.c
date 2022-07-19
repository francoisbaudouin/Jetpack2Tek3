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
    // if (size_array(str) != 2)
    //     return;
    // printf("je suis dans le id : %s\n", str[1]);
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
    for (int i = 0; client->actual.map[i]; i++) {
        printf("%s\n", client->actual.map[i]);
    }
    // SEND TO THE CLIENT
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
// printf("exec command\n");
    function_ptr_t commands[] = {
        {"ID", id},
        {"MAP", map},
        {"READY", ready},
        {"FIRE", fire},
        // {"START", start},
        // {"PLAYER", player},
        // {"COIN", coin},
        // {"FINISH", finish},
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
    printf("buffer from server: %s\n", buff);
}

void send_id(client_t *client)
{
    //send(client->fd, "ID", 3, 0);
    dprintf(client->fd, "ID\n");
}

void reply_from_serv(client_t *client, fd_set wfds)
{
    if (FD_ISSET(client->fd, &wfds)) {
        printf("a\n");
        send_id(client);
    }
    if (FD_ISSET(client->fd, &client->rfds))
        get_answer(client);
}

int cli_to_serv(client_t *client)
{
    fd_set wfds;
    fd_set wfds_tmp;
    fd_set rfds_tmp;
    FD_ZERO(&rfds_tmp);
    FD_ZERO(&wfds_tmp);
    FD_ZERO(&wfds);
    while (1) {
        FD_SET(client->fd, &wfds);
        FD_SET(client->fd, &client->rfds);
        rfds_tmp = client->rfds;
        wfds_tmp = wfds;
        if (select(FD_SETSIZE, &rfds_tmp, &wfds_tmp, NULL, NULL) == -1) {
            perror("select()");
            return (-1);
        } else {
            reply_from_serv(client, wfds);
        }   
    }
    return (0);
}

int main(int ac, char **av) 
{
    client_t *client = malloc(sizeof(client_t));
    char *buffer = strdup("MAP 8 4 ____e____c___e__c\n____e____c___e__c\n____e____c___e__c\n");
    // char *buffer = strdup("ID puto");
    client->ready = false;
    client->fire = false;
    client->start = false;
    if (check_args(ac, av, client) == -1)
        return (84);
    if (init_cli(client) == -1)
        return (84);
    // char **str;
    // int i = 0;
    // str = split_string(str, buffer, " ");
    // exec_player_command(client, str);

    cli_to_serv(client);
    // if (pthread_create(&client->thread, NULL, &cli_to_serv, client) != 0) {
    //     perror("pthread_create() afficher :");
    //     return (84);
    // }
    // if (pthread_join(client->thread, NULL) != 0) {
    //     perror("pthread_join() afficher :");
    //     return (84);
    // }
    return 0;
}