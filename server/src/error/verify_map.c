/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** verify_map
*/

#include "server.h"

#define COIN 'c'
#define ELECTRIC_FENCE 'e'
#define EMPTY_SPACE '_'

bool is_good_character(char *line)
{
    for (size_t i = 0; line[i] != '\n' && line[i] != '\0'; i++) {
        if (line[i] != COIN 
            && line[i] != ELECTRIC_FENCE
            && line[i] != EMPTY_SPACE) {
            return (false);
        }
    }
    return (true);
}
