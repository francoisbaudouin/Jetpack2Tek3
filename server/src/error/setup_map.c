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

static bool store_map(server_t *server, char *line, int i)
{
    server->map->map[i] = strdup(line);
    if (server->map->map[i] == NULL)
        return (true);
    return (false);
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

static bool load_file_in_mem(server_t *server, char const *filepath)
{
    FILE *fp = fopen(filepath, "r");
    size_t len = 0;
    char *line;
    size_t save_high = 0;
    size_t save_width = 0;
    bool first_line = true;

    while (getline(&line, &len, fp) != -1) {
        if (map_cmp_width(len, save_width, first_line) == false)
            return (false);
        first_line = false;
        save_width = len;
        if (store_map(server, line, len) == false)
            return (false);
        save_width++;
    }
    server->map->high = save_high;
    server->map->width = save_width;
    fclose(fp);
    free(line);
    return (true);
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