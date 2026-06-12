/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** menu.c
*/

#include "wolf.h"

void render_menu(sfRenderWindow *window, global_t *glb)
{
    if (glb->sprite) {
        sfRenderWindow_drawSprite(window, glb->sprite, NULL);
    }
    if (glb->init_sprite)
        sfRenderWindow_drawSprite(window, glb->init_sprite->sprite, NULL);
}
