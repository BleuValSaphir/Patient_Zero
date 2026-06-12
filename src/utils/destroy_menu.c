/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** destroy_menu.c
*/

#include "wolf.h"

void destroy_menu(global_t *glb)
{
    if (glb->texture) {
        sfTexture_destroy(glb->texture);
        glb->texture = NULL;
    }
    if (glb->sprite) {
        sfSprite_destroy(glb->sprite);
        glb->sprite = NULL;
    }
    if (glb->init_sprite)
        destroy_sprite(glb->init_sprite);
    if (glb->goodbye_sound) {
        destroy_sound(glb->goodbye_sound);
        glb->goodbye_sound = NULL;
    }
}
