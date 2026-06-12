/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** items
*/

#include <wolf.h>

#ifndef ITEMS_H
    #define ITEMS_H

    #define ITEM_LIST &glb->game->items.items_list

typedef enum item_type_e {
    MONEY,
    HEALTH
} item_type_t;

typedef struct items_list_s {
    item_type_t type;
    int quantity;
    sfVector2f pos;
    bool is_around;
    bool is_pick_up;
    bool to_delete;
    struct items_list_s *next;
} items_list_t;

typedef struct items_s {
    struct sound_effect_s *pick_up_sound;
    struct sound_effect_s *ping_sound;
    struct text_s *text;
    items_list_t *items_list;
    bool is_item;
    struct sprite_s *sprite;
    struct sprite_s *sprite_health;
} items_t;

void add_items(items_list_t **items, double x, double y,
    item_type_t type);
int remove_item(items_list_t **list);
void init_items(items_t *items);
void render_items(global_t *glb);
void destroy_items(items_t *item);
void update_items(global_t *glb);
void handle_items_event(items_list_t *list, sfEvent *event,
    global_t *glb);
void render_items_sprites(global_t *glb);
void spawn_random_items(global_t *glb);

#endif
