/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** update_vignette
*/

#include "game.h"

static void handle_narrowing(vignette_t *vignette)
{
    if (vignette->radius <= vignette->min_radius) {
        vignette->is_increasing = false;
    }
    if (vignette->is_increasing) {
        vignette->radius -= vignette->increase_var;
        vignette->red += vignette->red_incr;
        vignette->color.x = vignette->red;
    }
}

static void handle_dilation(vignette_t *vignette)
{
    if (vignette->radius >= vignette->base_radius) {
        vignette->is_getting_hit = false;
    }
    if (!vignette->is_increasing) {
        vignette->radius += vignette->decrease_var;
        vignette->red -= vignette->red_decr;
        vignette->color.x = vignette->red;
    }
}

static void update_color(shaders_t **shader, vignette_t *vignette)
{
    if (!*shader)
        return;
    sfShader_setFloatUniform((*shader)->shader, "radius", vignette->radius);
    sfShader_setVec3Uniform((*shader)->shader, "color", vignette->color);
}

void update_vignette(global_t *glb)
{
    sfTime time;
    float second = 0.;

    if (!glb->game->vignette.clock)
        return;
    time = sfClock_getElapsedTime(glb->game->vignette.clock);
    second = sfTime_asMilliseconds(time);
    if (second > 0.1) {
        if (glb->game->vignette.is_getting_hit == true) {
            handle_narrowing(&glb->game->vignette);
            handle_dilation(&glb->game->vignette);
            update_color(&glb->game->shader[VIGNETTE], &glb->game->vignette);
        }
        sfClock_restart(glb->game->vignette.clock);
    }
}
