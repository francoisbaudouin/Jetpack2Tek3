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

#define COIN 'c'
#define ELECTRIC_FENCE 'e'
#define EMPTY_SPACE ' '

static bool store_map(server_t *server, char *line, size_t len, int i)
{
    server->map->map[i] = strdup(line);
    if (server->map->map[i] == NULL)
        return (true);
    return (false);
}

static bool is_good_character(char c)
{
    if (c != EMPTY_SPACE
        || c != COIN
        || c != ELECTRIC_FENCE
        || c != '\n'
        || c != '\0')
        return (false);
    return (true);
}

static bool load_file_in_mem(server_t *server, char const *filepath)
{
    FILE *fp = fopen(filepath, "r");
    size_t len = 0;
    char *line;
    int i = 0;
    while (getline(&line, &len, fp) != -1) {
        if (store_map(server, line, len, i) == false)
            return (false);
        i++;
    }
    (void) len;
    fclose(fp);
    free(line);
}

bool load_map(server_t *server, char **argv)
{
    if (strcmp(argv[6], "-m") != 0)
        return (false);
    server->map = malloc(sizeof(map_t));
    load_file_in_mem(server, argv[7]);
    if (server->map == NULL)
        return (false);
    return (true);
}