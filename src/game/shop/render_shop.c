/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** render_shop.c
*/

#include "wolf.h"

static void render_shop_articles(sfRenderWindow *window, shop_t *shop)
{
    for (int i = 0; i < NB_ARMORY_EMPLACEMENT; i++) {
        if (shop->articles[i])
            sfRenderWindow_drawRectangleShape(window, shop->articles[i], NULL);
        if (shop->schema[i])
            sfRenderWindow_drawSprite(window, shop->schema[i]->sprite, NULL);
        if (shop->article_price[i])
            sfRenderWindow_drawText(window, shop->article_price[i]->text, NULL);
    }
}

void render_shop(sfRenderWindow *window, shop_t *shop)
{
    if (!shop->in_shop)
        return;
    for (int i = 0; i < NB_CATEGORIES; i++) {
        if (shop->categories[i])
            sfRenderWindow_drawRectangleShape(window,
                shop->categories[i], NULL);
        if (shop->categories_name[i])
            sfRenderWindow_drawText(window,
                shop->categories_name[i]->text, NULL);
    }
    render_shop_articles(window, shop);
    if (shop->money_shape)
        sfRenderWindow_drawCircleShape(window, shop->money_shape, NULL);
    if (shop->money_text)
        sfRenderWindow_drawText(window, shop->money_text->text, NULL);
}
