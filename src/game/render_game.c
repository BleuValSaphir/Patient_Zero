/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** render.c
*/

#include "wolf.h"

void render_wall_column(global_t *glb, int column, float wall_height,
    float brightness)
{
    sfVertex *v1 = sfVertexArray_getVertex(glb->wall_array, column * 2);
    sfVertex *v2 = sfVertexArray_getVertex(glb->wall_array, column * 2 + 1);
    sfColor color = sfColor_fromRGBA((sfUint8)brightness,
        (sfUint8)brightness, (sfUint8)brightness, 255);
    float start_y = (SCREEN_HEIGHT - wall_height) / 2.0f + glb->player.pitch;
    float end_y = start_y + wall_height;

    v1->position = (sfVector2f){(float)column, start_y};
    v2->position = (sfVector2f){(float)column, end_y};
    v1->color = color;
    v2->color = color;
    v1->texCoords = (sfVector2f){(float)glb->player.tex_x, 0};
    v2->texCoords = (sfVector2f){
        (float)glb->player.tex_x, (float)glb->player.tex_size.y};
}
