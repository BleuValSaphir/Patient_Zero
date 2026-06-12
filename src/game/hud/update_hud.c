/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** update_hud.c
*/

#include "wolf.h"

static void update_hud_visuals(global_t *glb)
{
    float hp_ratio = (float)glb->player.health / glb->player.health_max;

    if (hp_ratio < 0.0f)
        hp_ratio = 0.0f;
    if (glb->hud->health_bar) {
        sfRectangleShape_setSize(glb->hud->health_bar,
            (sfVector2f){150.0f * hp_ratio, 6.0f});
        if (hp_ratio <= 0.2f)
            sfRectangleShape_setFillColor(glb->hud->health_bar,
                sfColor_fromRGB(200, 50, 50));
        else
            sfRectangleShape_setFillColor(glb->hud->health_bar, sfWhite);
    }
}

void update_hud(global_t *glb, bool action_triggered)
{
    if (!glb->hud)
        return;
    if (glb->player.health != glb->hud->last_health) {
        action_triggered = true;
        glb->hud->last_health = glb->player.health;
    }
    if (glb->game->inventory->cur_index != glb->hud->last_weapon_index) {
        action_triggered = true;
        glb->hud->last_weapon_index = glb->game->inventory->cur_index;
    }
    if (action_triggered || TYPE == KNIFE || TYPE == SPECIAL ||
        sfKeyboard_isKeyPressed(sfKeyI)) {
        glb->hud->is_visible = true;
        glb->hud->display_timer = 3.0f;
    }
    glb->hud->display_timer -= glb->hud->is_visible ? 0.1f : 0.0f;
    if (glb->hud->display_timer <= 0.0f)
        glb->hud->is_visible = false;
    update_hud_visuals(glb);
}
