/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** init_cinematic.c
*/

#include "wolf.h"

void init_cinematic(global_t *glb)
{
    glb->cinematic_txt = set_text(&sfWhite,
        &(sfVector2f){50.f, 50.f}, &(text_info_t)
        {"assets/font/Roboto.ttf", "", 50});
    glb->cinematic_clock = sfClock_create();
    glb->typewriter_clock = sfClock_create();
    glb->text_index = 0;
    glb->cinematic_step = 0;
    glb->end_cinematic = false;
    glb->target_text[0] = '\0';
    glb->current_text[0] = '\0';
}
