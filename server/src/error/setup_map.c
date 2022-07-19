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

static void get_nb_line(char const *file, server_t *server)
{
    size_t nb_line = 0;
    FILE *fp = fopen(file, "r");
    char *line = NULL;
    size_t len = 0;

    if (fp == NULL)
        return;
    while (getline(&line, &len, fp) != -1)
        nb_line++;
    fclose(fp);
    server->map->high = nb_line;
}

static bool store_map(server_t *server, char *line, size_t len ,size_t i)
{
    (void) len;
    if (is_good_character(line) == false) {
        return (false);
    }
    server->map->map[i] = strdup(line);
    if (server->map->map[i] == NULL)
        return (false);
    return (true);
}

static bool map_cmp_width(size_t len, size_t save_len, bool first_line)
{
    if (first_line == true)  {
        return (true);
    }
    if (len == save_len)
        return (true);
    return (false);
}

static bool load_file(server_t *server, char const *filepath)
{
    FILE *fp = fopen(filepath, "r");
    size_t len = 0;
    char *line;
    size_t save_width = 0;
    bool first_line = true;
    int end = 0;

    if (fp == NULL) {
        return (false);
    }
    get_nb_line(filepath, server);
    server->map->map = malloc(sizeof(char *) * (server->map->high + 1));
    while (true) {
        end = getline(&line, &len, fp);
        if (end == -1)
            break;
        if (map_cmp_width(len, save_width, first_line) == false) 
            return (false);
        first_line = false;
        save_width = len;
        if (store_map(server, line, len, save_width) == false)
            return (false);
    }
    server->map->width = save_width;
    fclose(fp);
    free(line);
    return (true);
}

server_t *load_map(server_t *server, char *path)
{
    printf("avant\n");
    server->map = malloc(sizeof(map_t));
    if (load_file(server, path) == false) {
        return (NULL);
    }
    return (server);
}