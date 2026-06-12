/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** update_game.c
*/

#include "wolf.h"

void check_pick_up_items(global_t *glb, items_list_t *tmp, bool *pick_up)
{
    if (tmp->is_pick_up == true) {
        *pick_up = true;
        if (tmp->type == MONEY) {
            glb->game->inventory->money += tmp->quantity;
        }
        tmp->to_delete = true;
    }
}

void update_pick_up_items(global_t *glb, items_list_t **list, sfEvent *event)
{
    items_list_t *tmp = *list;
    bool pick_up = false;

    while (tmp) {
        check_pick_up_items(glb, tmp, &pick_up);
        tmp = tmp->next;
    }
    if (pick_up)
        sfSound_play(glb->game->items.pick_up_sound->sound);
    while (remove_item(list) != 0);
}

static void manage_fade(global_t *glb)
{
    enemy_t *dg = NULL;
    float dx = 0;
    float dy = 0;
    float dist = 100.0f;

    for (int i = 0; i < glb->game->enemy_count; i++)
        if (glb->game->enemies[i].attack_cooldown == -100 &&
            glb->game->enemies[i].state != E_DEAD)
            dg = &glb->game->enemies[i];
    if (dg) {
        dx = glb->player.x - dg->pos.x;
        dy = glb->player.y - dg->pos.y;
        dist = sqrt(dx * dx + dy * dy);
    }
    if (dg && dist < 3.0f)
        glb->fade_alpha = 255 - (int)((dist / 3.0f) * 255.0f);
    else if (glb->fade_alpha > 0)
        glb->fade_alpha -= 3;
    if (glb->fade_alpha < 0)
        glb->fade_alpha = 0;
}

static void update_game_over_state(global_t *glb)
{
    if (glb->game->game_over_fade < 255.0f) {
        glb->game->game_over_fade += 100.0f * glb->dt;
        if (glb->game->game_over_fade > 255.0f)
            glb->game->game_over_fade = 255.0f;
    }
    handle_hover_anim(glb->window, glb->game->game_over_restart);
    handle_hover_anim(glb->window, glb->game->game_over_menu);
}

static void update_pause_menu_state(global_t *glb, sfEvent *event)
{
    handle_hover_anim(glb->window, glb->game->pause_resume);
    handle_hover_anim(glb->window, glb->game->pause_settings);
    handle_hover_anim(glb->window, glb->game->pause_main_menu);
    handle_hover_anim(glb->window, glb->game->save_text);
}

void static handle_update(global_t *glb, bool action_triggered,
    sfEvent *event)
{
    if (!SHOP.in_shop) {
        update_weapon_actions(glb);
        update_items(glb);
        update_pick_up_items(glb, &glb->game->items.items_list, event);
        update_mouse(&glb->player, glb->window, glb);
    } else
        update_shop(glb);
    update_player(glb);
    update_enemies(glb);
    update_hud(glb, action_triggered);
    update_particles(glb);
    update_vignette(glb);
}

void update_game(global_t *glb, sfEvent *event)
{
    bool action_triggered = false;

    if (!glb || !glb->game)
        return;
    if (glb->player.health <= 0) {
        update_game_over_state(glb);
        return;
    }
    if (glb->game->paused) {
        if (glb->game->in_settings) {
            update_settings(glb, event);
        } else {
            update_pause_menu_state(glb, event);
        }
        return;
    }
    manage_fade(glb);
    action_triggered = glb->game->shoot_info.is_shoting
        || glb->game->shoot_info.reload;
    handle_update(glb, action_triggered, event);
}
