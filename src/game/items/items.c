/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** items
*/

#include "items.h"

static void free_item_list(items_list_t *list)
{
    items_list_t *to_free = NULL;

    while (list) {
        to_free = list;
        list = list->next;
        free(to_free);
    }
}

void destroy_items(items_t *item)
{
    if (!item)
        return;
    if (item->pick_up_sound)
        destroy_sound(item->pick_up_sound);
    if (item->ping_sound)
        destroy_sound(item->ping_sound);
    if (item->text)
        destroy_text(item->text);
    if (item->sprite)
        destroy_sprite(item->sprite);
    if (item->sprite_health)
        destroy_sprite(item->sprite_health);
    free_item_list(item->items_list);
}

static int check_delete(items_list_t *cur)
{
    while (cur) {
        if (cur->to_delete == true)
            return 1;
        cur = cur->next;
    }
    return 0;
}

int remove_item(items_list_t **list)
{
    items_list_t *prev = NULL;
    items_list_t *cur = *list;

    if (check_delete(cur) == 0)
        return 0;
    while (cur && cur->to_delete == false) {
        prev = cur;
        cur = cur->next;
    }
    if (prev)
        prev->next = cur->next;
    else
        *list = cur->next;
    free(cur);
    return 1;
}

void add_items(items_list_t **items, double x, double y, item_type_t type)
{
    items_list_t *node = malloc(sizeof(items_list_t));

    if (!node)
        return;
    node->type = type;
    node->quantity = 180 + (rand() % 40);
    node->pos = (sfVector2f){x, y};
    node->is_around = false;
    node->is_pick_up = false;
    node->to_delete = false;
    node->next = *items;
    *items = node;
}

void init_items(items_t *items)
{
    text_info_t info = {"assets/font/Coolvetica Rg It.otf",
        "Press E to get items", 50};
    sfVector2f pos = {15., 0.};

    items->is_item = false;
    items->items_list = NULL;
    items->sprite = set_sprite("assets/sprites/money.png", NULL, NULL, NULL);
    items->sprite_health = set_sprite("assets/sprites/kit_bag.png", NULL,
        NULL, NULL);
    items->text = set_text(&(sfColor){150, 50, 50, 230}, &pos, &info);
    items->ping_sound = set_sound("assets/sounds/ping.mp3", 70);
    if (!items->ping_sound)
        return;
    items->pick_up_sound = set_sound("assets/sounds/pick-up.mp3", 70);
    if (!items->pick_up_sound)
        return;
}

void spawn_random_items(global_t *glb)
{
    int placed = 0;
    int rx = 0;
    int ry = 0;
    int item_count = MAP_HEIGHT * MAP_WIDTH / 200.0;

    while (placed < item_count) {
        rx = rand() % MAP_WIDTH;
        ry = rand() % MAP_HEIGHT;
        if (glb->map[ry][rx] == 0) {
            add_items(&glb->game->items.items_list, (double)rx + 0.5,
                (double)ry + 0.5, HEALTH);
            placed++;
        }
    }
}
