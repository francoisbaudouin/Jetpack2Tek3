/*
** EPITECH PROJECT, 2021
** list
** File description:
** list
*/

#include "server.h"

list_t *initialization(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (list == NULL) {
        return (NULL);
    }
    list->first = NULL;
    list->size = 0;
    return (list);
}

list_t *insertion(list_t *list, player_t *player)
{
    element_t *new = malloc(sizeof(element_t));

    if (list == NULL || new == NULL)
        return (NULL);
    new->player = player;
    new->next = list->first;
    list->first = new;
    list->size++;
    return (list);
}

list_t *insertion_end(list_t *list, player_t *player)
{
    element_t *new = malloc(sizeof(element_t));
    element_t *temp = list->first;

    if (list == NULL || new == NULL)
        return (NULL);
    new->player = player;
    new->next = NULL;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
    list->size++;
    return (list);
}

list_t *delete_first_elem(list_t *list)
{
    element_t *del;

    if (list == NULL)
        return NULL;
    if (list->first != NULL) {
        del = list->first;
        list->first = list->first->next;
        free(del);
    }
    list->size--;
    return (list);
}

list_t *delete_last_elem(list_t *list)
{
    element_t *tmp = list->first;
    element_t *del;

    if (list == NULL)
        return NULL;
    while (tmp->next->next != NULL) {
        tmp = tmp->next;
    }
    del = tmp->next;
    tmp->next = NULL;
    free(del);
    list->size--;
    return (list);
}
