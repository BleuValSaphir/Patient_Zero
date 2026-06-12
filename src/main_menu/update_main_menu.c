/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** update_main_menu.C
*/

#include "wolf.h"

static void play_epilogue_sound(global_t *glb)
{
    if (!glb->epilogue_sound || glb->epilogue_sound->played)
        return;
    if (!glb->epilogue_sound->sound)
        return;
    glb->epilogue_sound->delay += glb->dt;
    if (glb->epilogue_sound->delay > 0.2f) {
        sfSound_play(glb->epilogue_sound->sound);
        glb->epilogue_sound->played = true;
    }
}

void update_main_menu(global_t *glb, sfEvent *event)
{
    (void)event;
    play_epilogue_sound(glb);
    handle_hover_anim(glb->window, glb->init_text);
    handle_hover_anim(glb->window, glb->load_txt);
    handle_hover_anim(glb->window, glb->settings_txt);
    handle_hover_anim(glb->window, glb->quit_txt);
}
