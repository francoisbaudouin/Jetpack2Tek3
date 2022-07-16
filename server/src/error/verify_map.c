/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** verify_map
*/

#include "server.h"
#define COIN 'c'
#define ELECTRIC_FENCE 'e'
#define EMPTY_SPACE ' '

static bool is_good_character(char *line, size_t len)
{
    for (size_t i = 0; i < len; i++)
        if (line[i] != EMPTY_SPACE
            || line[i] != COIN
            || line[i] != ELECTRIC_FENCE
            || line[i] != '\n'
            || line[i] != '\0')
            return (false);
    return (true);
}