/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** setup_map
*/

#include "server.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char **read_file(char *av, char **buffer, server_t *server)
{
    FILE * fp = fopen(av, "r");
    int y = 0;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1) {
        server->map->width = strlen(line);
        buffer[y] = malloc(sizeof(char) * strlen(line));
        buffer[y] = strdup(line);
        y++;
    }
    server->map->high = y;
    buffer[y] = NULL;
    fclose(fp);
    if (line)
        free(line);
    return (buffer);
}

void load_map(server_t *server, char *path)
{
    server->map = malloc(sizeof(map_t));
    server->map->map = malloc(sizeof(char *)*50);
    read_file(path, server->map->map, server);
}
