/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** update_item
*/

#include "game.h"

static void apply_item_effect(items_list_t *tmp, global_t *glb)
{
    if (tmp->type == HEALTH) {
        glb->game->inventory->indexes[MEDKIT] = MEDKIT;
        glb->game->inventory->cur_ammunation[MEDKIT]++;
    }
}

void item_loop(items_list_t *list, global_t *glb)
{
    items_list_t *tmp = list;

    while (tmp) {
        if (tmp->is_around) {
            tmp->is_pick_up = true;
            apply_item_effect(tmp, glb);
        } else
            tmp->is_pick_up = false;
        tmp = tmp->next;
    }
}

void handle_items_event(items_list_t *list, sfEvent *event, global_t *glb)
{
    bool e_pressed = event->type == sfEvtKeyReleased &&
        event->key.code == sfKeyE;
    bool a_pressed = event->type == sfEvtJoystickButtonReleased &&
        event->joystickButton.button == 0;

    if (e_pressed || a_pressed)
        item_loop(list, glb);
}

void check_if_item(global_t *glb, items_list_t *item, bool *is_item)
{
    float cx = glb->player.x - item->pos.x;
    float cy = glb->player.y - item->pos.y;

    if (cx < 0)
        cx *= -1.;
    if (cy < 0)
        cy *= -1.;
    if (cx < 1. && cy < 1.) {
        *is_item = true;
        item->is_around = true;
    } else
        item->is_around = false;
}

void update_items(global_t *glb)
{
    bool is_item = false;
    items_list_t *tmp = glb->game->items.items_list;

    while (tmp) {
        check_if_item(glb, tmp, &is_item);
        tmp = tmp->next;
    }
    if (glb->game->items.is_item == false && is_item == true)
        sfSound_play(glb->game->items.ping_sound->sound);
    glb->game->items.is_item = is_item;
}
