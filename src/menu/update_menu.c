/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** update_menu.c
*/

#include "wolf.h"

static void play_menu_sound(global_t *glb)
{
    if (!glb->goodbye_sound || glb->goodbye_sound->played)
        return;
    if (!glb->goodbye_sound->sound)
        return;
    glb->goodbye_sound->delay += glb->dt;
    if (glb->goodbye_sound->delay > 0.2f) {
        sfSound_play(glb->goodbye_sound->sound);
        glb->goodbye_sound->played = true;
    }
}

void update_menu(global_t *glb, sfEvent *event)
{
    sprite_t *enter = glb->init_sprite;
    float seconds;

    (void)event;
    play_menu_sound(glb);
    if (!enter || !enter->clock || !enter->sprite)
        return;
    seconds = sfClock_getElapsedTime(enter->clock).microseconds / 1000000.0f;
    if (seconds > 0.25f) {
        enter->rect.left += 64;
        if (enter->rect.left >= 192)
            enter->rect.left = 0;
        sfSprite_setTextureRect(enter->sprite, enter->rect);
        sfClock_restart(enter->clock);
    }
}
