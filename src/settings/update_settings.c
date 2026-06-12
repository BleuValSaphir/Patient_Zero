/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** update_settings.c
*/

#include "wolf.h"

void update_settings(global_t *glb, sfEvent *event)
{
    handle_color_anim(glb->window, glb->full_screen_txt);
    handle_color_anim(glb->window, glb->audio_txt);
    handle_color_anim(glb->window, glb->toggle_txt);
    handle_color_anim(glb->window, glb->arrow_left);
    handle_color_anim(glb->window, glb->arrow_right);
    handle_color_anim(glb->window, glb->exit_txt);
    handle_color_anim(glb->window, glb->sens_left);
    handle_color_anim(glb->window, glb->sens_right);
    handle_color_anim(glb->window, glb->headbobbing_toggle);
    handle_color_anim(glb->window, glb->sens_txt);
    handle_color_anim(glb->window, glb->headbobbing_txt);
    handle_color_anim(glb->window, glb->layout_txt);
    handle_color_anim(glb->window, glb->layout_toggle);
    handle_color_anim(glb->window, glb->fps_txt);
    handle_color_anim(glb->window, glb->fps_left);
    handle_color_anim(glb->window, glb->fps_right);
}
