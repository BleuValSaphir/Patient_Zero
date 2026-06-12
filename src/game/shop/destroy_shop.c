/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** destroy_shop
*/

#include "game.h"

static void destroy_categories(shop_t *shop)
{
    for (int i = 0; i < NB_CATEGORIES; i++) {
        if (shop->categories[i])
            sfRectangleShape_destroy(shop->categories[i]);
        if (shop->categories_name[i])
            destroy_text(shop->categories_name[i]);
    }
}

static void destroy_armory(shop_t *shop)
{
    for (int i = 0; i < NB_ARMORY_EMPLACEMENT; i++) {
        if (shop->articles[i])
            sfRectangleShape_destroy(shop->articles[i]);
        if (shop->schema[i])
            destroy_sprite(shop->schema[i]);
        if (shop->article_price[i])
            destroy_text(shop->article_price[i]);
    }
}

void destroy_shop(shop_t *shop)
{
    if (!shop)
        return;
    destroy_armory(shop);
    destroy_categories(shop);
    if (shop->money_shape)
        sfCircleShape_destroy(shop->money_shape);
    if (shop->money_text)
        destroy_text(shop->money_text);
}
