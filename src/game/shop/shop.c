/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** shop
*/

#include "wolf.h"

void update_shop(global_t *glb)
{
    sfFloatRect bounds = sfText_getLocalBounds(SHOP.money_text->text);
    sfVector2f origin = {
        bounds.left + bounds.width / 2.,
        bounds.top + bounds.height / 2.
    };
    char money_count[16];

    sfText_setOrigin(SHOP.money_text->text, origin);
    sprintf(money_count, "%d", INVENTORY->money);
    sfText_setString(SHOP.money_text->text, money_count);
}

static void init_shop_rectangle(sfRectangleShape *rect, sfVector2f *dimensions,
    sfVector2f *pos, sfColor *color)
{
    sfColor color2 = *color;

    sfRectangleShape_setSize(rect, *dimensions);
    sfRectangleShape_setOutlineThickness(rect, 8.);
    sfRectangleShape_setOutlineColor(rect, *color);
    color2.a = 50;
    color2.r = 80;
    sfRectangleShape_setFillColor(rect, color2);
    sfRectangleShape_setOrigin(rect, (sfVector2f){(*dimensions).x / 2,
            (*dimensions).y / 2});
    sfRectangleShape_setPosition(rect, *pos);
}

static void actualise_pos(sfVector2f *pos, sfVector2f *dimensions,
    sfVector2f *offset, int index)
{
    (*pos).x += (*dimensions).x + (*offset).x;
    if (index == NB_ARMORY_EMPLACEMENT / 2) {
        (*pos).y += (*dimensions).y + (*offset).y;
        (*pos).x = SCREEN_WIDTH / 5 + (*dimensions).x + (*offset).x;
    }
}

static int init_variables(shop_t *shop)
{
    float radius = SCREEN_HEIGHT * 0.139;
    sfVector2f pos = {SCREEN_WIDTH * 0.2, SCREEN_HEIGHT * 0.65};
    sfColor icolor = sfColor_fromRGBA(40, 40, 160, 150);
    sfColor ocolor = sfColor_fromRGB(40, 40, 200);
    text_info_t info_text = {"assets/font/Coolvetica Rg It.otf",
        "N/A", 50};

    shop->money_shape = set_circle(radius, &pos, &icolor, &ocolor);
    pos.y += 50;
    shop->money_text = set_text(&sfWhite, &pos, &info_text);
    if (!shop->money_shape || !shop->money_text)
        return ERROR;
    shop->in_shop = false;
    return SUCCESS;
}

static void init_cat_text(shop_t *shop, int index)
{
    sfFloatRect bounds =
        sfText_getLocalBounds(shop->categories_name[index]->text);
    sfVector2f origin = {
        bounds.left + bounds.width / 2.,
        bounds.top + bounds.height / 2.
    };

    sfText_setOrigin(shop->categories_name[index]->text, origin);
}

static int init_categories(shop_t *shop)
{
    sfColor color = sfColor_fromRGBA(150, 0, 10, 150);
    sfVector2f size = {SCREEN_WIDTH / 6, SCREEN_HEIGHT * 0.045};
    sfVector2f pos = {SCREEN_WIDTH / 5, (SCREEN_HEIGHT * 0.16)};
    sfVector2f offset = {60, 60};
    char *name[] = {"SPECIAL", "pistol M1911", "MP5", NULL};
    text_info_t info_text = {"assets/font/Roboto.ttf", "N/A", 40};

    for (int i = 0; i < NB_CATEGORIES; i++) {
        shop->categories[i] = set_rectangle(&size, &color, &pos);
        if (!shop->categories[i])
            return ERROR;
        shop->categories_name[i] = set_text(&sfWhite, &pos, &info_text);
        if (!shop->categories_name[i])
            return ERROR;
        sfText_setString(shop->categories_name[i]->text, name[i]);
        init_cat_text(shop, i);
        actualise_pos(&pos, &size, &offset, i);
    }
    return SUCCESS;
}

static int init_single_schema(shop_t *shop, int i, sfVector2f *dim,
    sfVector2f *pos)
{
    sfColor color = sfColor_fromRGB(100, 0, 20);
    sfVector2u tex_size;
    float scale_f;

    shop->articles[i] = sfRectangleShape_create();
    if (!shop->articles[i])
        return ERROR;
    init_shop_rectangle(shop->articles[i], dim, pos, &color);
    shop->schema[i] = set_sprite(schema[i].filepath, &schema[i].scale,
        &schema[i].origin, pos);
    if (!shop->schema[i])
        return ERROR;
    tex_size = sfTexture_getSize(shop->schema[i]->texture);
    sfSprite_setOrigin(shop->schema[i]->sprite, (sfVector2f)
        {tex_size.x / 2.0f, tex_size.y / 2.0f});
    scale_f = (dim->x * 1.5f) / (float)tex_size.x;
    if ((dim->y * 0.8f) / (float)tex_size.y < scale_f)
        scale_f = (dim->y * 0.8f) / (float)tex_size.y;
    sfSprite_setScale(shop->schema[i]->sprite, (sfVector2f){scale_f, scale_f});
    return SUCCESS;
}

static int init_schema(shop_t *shop)
{
    sfVector2f dimensions = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 4};
    sfVector2f pos = {SCREEN_WIDTH / 5, SCREEN_HEIGHT / 3};
    sfVector2f offset = {60, 60};

    for (int i = 0; i < NB_ARMORY_EMPLACEMENT; i++) {
        if (init_single_schema(shop, i, &dimensions, &pos) == ERROR)
            return ERROR;
        init_article_price(shop, i, &pos, &dimensions);
        actualise_pos(&pos, &dimensions, &offset, i);
    }
    return SUCCESS;
}

int init_shop(shop_t *shop)
{
    if (init_schema(shop) == ERROR)
        return ERROR;
    if (init_categories(shop) == ERROR)
        return ERROR;
    return (init_variables(shop) == ERROR) ? ERROR : SUCCESS;
}
