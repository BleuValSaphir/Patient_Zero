/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** inventory
*/

#include "inventory.h"

int init_inventory(inventory_t **inv)
{
    *inv = malloc(sizeof(inventory_t));
    if (!inv)
        return ERROR;
    for (int i = 0; i < NB_WEAPON; i++) {
        (*inv)->indexes[i] = KNIFE;
        (*inv)->cur_ammunation[i] = 20;
    }
    (*inv)->money = 0;
    (*inv)->cur_index = 0;
    return SUCCESS;
}
