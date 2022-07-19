/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** split_str
*/

#include "../include/client.h"

int count_space(char *str, char delim)
{
    int count = 0;
    for (size_t i = 0; str[i]; i++) {
        if (str[i] == delim)
            count++;
    }  
    return (count);
}

char **split_string(char **str, char *buffer, char *delimiter)
{
    char s = delimiter[0];
    str = malloc(sizeof(char*) * (count_space(buffer, s) + 1));
    int i = 0;
    char *split_str;
    split_str = strtok(buffer, delimiter);
    while ( split_str != NULL ) {
        str[i] = strdup(split_str);
        i++;
        split_str = strtok (NULL, delimiter);
    }
    str[i] = NULL;
    return (str);
}
