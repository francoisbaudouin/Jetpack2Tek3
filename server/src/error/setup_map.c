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

#define COIN 'c'
#define ELECTRIC_FENCE 'e'
#define EMPTY_SPACE ' '

static void store_map(server_t *server, char *line, size_t len)
{
    
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

static void load_file_in_mem(server_t *server, char const *filepath)
{
    FILE *fp = fopen(filepath, "r");
    size_t len = 0;
    char *line;

    while (getline(&line, &len, fp) != -1) {

    }
    fclose(fp);
    free(line);
}

bool load_map(server_t *server, char **argv)
{
    if (strcmp(argv[6], "-m") != 0)
        return (false);
    server->map = malloc(sizeof(map_t));
    if (server->map == NULL)
        return (false);
    return (true);
}