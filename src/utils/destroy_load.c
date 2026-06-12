/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** destroy_load.c
*/

#include "wolf.h"

void destroy_load(global_t *glb)
{
    if (!glb)
        return;
    if (glb->instruction) {
        destroy_text(glb->instruction);
        glb->instruction = NULL;
    }
    if (glb->texture) {
        sfTexture_destroy(glb->texture);
        glb->texture = NULL;
    }
    if (glb->sprite) {
        sfSprite_destroy(glb->sprite);
        glb->sprite = NULL;
    }
}
