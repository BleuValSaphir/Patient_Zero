/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** get_gun
*/

#include "game.h"

void get_gun_ammu(global_t *glb)
{
    int price = schema[ARTICLE_GUN_AMMU].price;

    if (INVENTORY->money >= price) {
        INVENTORY->cur_ammunation[GUN] += WEAPON[GUN].max_ammunation;
        INVENTORY->money -= price;
    }
}

void get_gun(global_t *glb)
{
    int price = schema[ARTICLE_GUN].price;

    if (INVENTORY->indexes[GUN] == KNIFE && INVENTORY->money >= price) {
        INVENTORY->indexes[GUN] = GUN;
        INVENTORY->money -= price;
        sfRectangleShape_setFillColor(ARTICLE[ARTICLE_GUN],
            sfRectangleShape_getOutlineColor(ARTICLE[ARTICLE_GUN]));
    }
}
