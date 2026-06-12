/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** handle_article_price
*/

#include "game.h"

int init_article_price(shop_t *shop, int index, sfVector2f *schema_pos,
    sfVector2f *dimensions)
{
    text_info_t info_text = {"assets/font/Roboto.ttf", "N/A", 30};
    sfVector2f pos = {
        (*schema_pos).x - (*dimensions).x / 2 + SCREEN_HEIGHT * 0.01,
        (*schema_pos).y + SCREEN_HEIGHT * 0.085
    };
    char price[9];

    sprintf(price, "%d", schema[index].price);
    shop->article_price[index] = set_text(&sfWhite, &pos, &info_text);
    if (!shop->article_price[index])
        return ERROR;
    sfText_setString(shop->article_price[index]->text, price);
    return SUCCESS;
}
