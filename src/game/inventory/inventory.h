/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** inventory
*/

#ifndef INVENTORY_H
    #define INVENTORY_H

    #include "wolf.h"

    #define NB_EMPLACEMENT 5

typedef struct inventory_s {
    char indexes[NB_EMPLACEMENT];
    char cur_index;
    int cur_ammunation[NB_EMPLACEMENT];
    int money;
} inventory_t;

int init_inventory(inventory_t **inv);

#endif
