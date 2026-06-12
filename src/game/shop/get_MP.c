/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** get_MP
*/

#include "game.h"

void get_mp_ammu(global_t *glb)
{
    int price = schema[ARTICLE_MP5_AMMU].price;

    if (INVENTORY->money >= price) {
        INVENTORY->cur_ammunation[MP5] += WEAPON[MP5].max_ammunation;
        INVENTORY->money -= price;
    }
}

void get_mp(global_t *glb)
{
    int price = schema[ARTICLE_MP5].price;

    if (INVENTORY->indexes[MP5] == KNIFE && INVENTORY->money >= price) {
        INVENTORY->indexes[MP5] = MP5;
        INVENTORY->money -= price;
        sfRectangleShape_setFillColor(ARTICLE[ARTICLE_MP5],
            sfRectangleShape_getOutlineColor(ARTICLE[ARTICLE_MP5]));
    }
}
