/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** shop
*/

#ifndef SHOP_H
    #define SHOP_H

    #include "wolf.h"

    #define COLOR_SHOP sfColor_fromRGB(100, 0, 20)

    #define SPECIAL_PRICE 5000
    #define GUN_PRICE 300
    #define GUN_AMMU_PRICE 100
    #define MP5_PRICE 800
    #define MP5_AMMU_PRICE 150

typedef struct schema_info_s {
    char *filepath;
    sfVector2f origin;
    sfVector2f scale;
    int price;
} schema_info_t;

static const schema_info_t schema[] = {
    {"assets/sprites/schema_special.png", {398., 470.}, {0.2, 0.2},
        SPECIAL_PRICE},
    {"assets/sprites/schema_gun.png", {1306., 816}, {0.2, 0.2},
        GUN_PRICE},
    {"assets/sprites/schema_MP.png", {1306., 675.}, {0.2, 0.2},
        MP5_PRICE},
    {"assets/sprites/schema_gun_ammu.png", {1306., 816}, {0.165, 0.165},
        GUN_AMMU_PRICE},
    {"assets/sprites/schema_MP_ammu.png", {653., 408.}, {0.3, 0.3},
        MP5_AMMU_PRICE},
    {0, 0, 0}
};

    #define NB_ARMORY_EMPLACEMENT 5

    #define ARTICLE glb->game->shop.articles
    #define ARTICLE_SPECIAL 0
    #define ARTICLE_GUN 1
    #define ARTICLE_MP5 2
    #define ARTICLE_GUN_AMMU 3
    #define ARTICLE_MP5_AMMU 4

    #define NB_CATEGORIES 3

typedef struct shop_s {
    bool in_shop;
    sfRectangleShape *articles[NB_ARMORY_EMPLACEMENT];
    struct text_s *article_price[NB_ARMORY_EMPLACEMENT];
    sfRectangleShape *categories[NB_CATEGORIES];
    struct text_s *categories_name[NB_CATEGORIES];
    sfCircleShape *money_shape;
    struct sprite_s *money_sprite;
    struct text_s *money_text;
    struct sprite_s *schema[NB_ARMORY_EMPLACEMENT];
    //sfClock *clock;
} shop_t;

int init_shop(shop_t *shop);
void destroy_shop(shop_t *shop);
void handle_shop_event(global_t *glb, sfEvent *event);
void render_shop(sfRenderWindow *window, shop_t *shop);
void update_shop(global_t *glb);
int init_article_price(shop_t *shop, int index, sfVector2f *schema_pos,
    sfVector2f *dimensions);

typedef void (*func_t)(global_t *glb);

void get_special(global_t *glb);
void get_gun(global_t *glb);
void get_gun_ammu(global_t *glb);
void get_mp(global_t *glb);
void get_mp_ammu(global_t *glb);

static const func_t get_item[] = {
    get_special,
    get_gun,
    get_mp,
    get_gun_ammu,
    get_mp_ammu,
    NULL
};

#endif
