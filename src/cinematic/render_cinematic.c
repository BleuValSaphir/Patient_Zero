/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** render_cinematic.c
*/

#include "wolf.h"

void render_cinematic(sfRenderWindow *window, global_t *glb)
{
    sfRectangleShape *rect;

    if (glb->cinematic_txt)
        sfRenderWindow_drawText(window, glb->cinematic_txt->text, NULL);
    if (glb->cinematic_step == 8 && glb->fade_alpha > 0) {
        rect = sfRectangleShape_create();
        sfRectangleShape_setSize(rect, (sfVector2f){1920.f, 1080.f});
        sfRectangleShape_setFillColor(rect,
            (sfColor){0, 0, 0, glb->fade_alpha});
        sfRenderWindow_drawRectangleShape(window, rect, NULL);
        sfRectangleShape_destroy(rect);
    }
}
