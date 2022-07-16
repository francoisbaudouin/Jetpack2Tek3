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
    int nb_line = 0;
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

static bool store_map(server_t *server, char *line, size_t i)
{
    if (is_good_character(line) == false) {
        return (false);
    }
    server->map->map[i] = strdup(line);
    printf("%s\n", server->map->map[i]);
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

    if (fp == NULL)
        return (false);
    printf("%zu\n", server->map->high);
    server->map->map = malloc(sizeof(char *) * (server->map->high + 1));
    while (getline(&line, &len, fp) == -1) {
        if (map_cmp_width(len, save_width, first_line) == false) {
            printf("Map have different width\n");
            return (false);
        }
        first_line = false;
        save_width = len;
        if (store_map(server, line, save_width) == false)
            return (false);
        free(line);

    }
    server->map->width = save_width;
    fclose(fp);
    free(line);
    return (true);
}

bool load_map(server_t *server, char **argv)
{
    if (strcmp(argv[5], "-m") != 0)
        return (false);
    server->map = malloc(sizeof(map_t));
    load_file(server, argv[6]);
    return (true);
}