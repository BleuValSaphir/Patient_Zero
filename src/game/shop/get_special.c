/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** get_special
*/

#include "game.h"

void get_special(global_t *glb)
{
    int price = schema[ARTICLE_SPECIAL].price;

    if (INVENTORY->indexes[SPECIAL] == KNIFE && INVENTORY->money >= price) {
        INVENTORY->indexes[SPECIAL] = SPECIAL;
        INVENTORY->money -= price;
        sfRectangleShape_setFillColor(ARTICLE[ARTICLE_SPECIAL],
            sfRectangleShape_getOutlineColor(ARTICLE[ARTICLE_SPECIAL]));
    }
}
