/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** draw_ennemy.c
*/

#include "wolf.h"

void draw_enemy(struct sprite_s *sprite_data, global_t *glb, int x,
    screen_pos_t *screen_pos)
{
    float floor_y = (SCREEN_HEIGHT / 2.0f) + glb->player.pitch +
        (glb->base_height / 2.0f) + (glb->base_height *
        screen_pos->z_offset);
    int tex_height = sprite_data->rect.height > 0 ?
        sprite_data->rect.height : (int)glb->tex_size.y;
    int tex_top = sprite_data->rect.top;
    sfIntRect rect = {glb->tex_x, tex_top, 1, tex_height};
    sfVector2f pos = {(float)x, floor_y - screen_pos->screen_height};
    sfVector2f scale = {1.0f, (float)screen_pos->screen_height /
        tex_height};

    sfSprite_setTextureRect(sprite_data->sprite, rect);
    sfSprite_setPosition(sprite_data->sprite, pos);
    sfSprite_setScale(sprite_data->sprite, scale);
    sfRenderTexture_drawSprite(glb->game->rt, sprite_data->sprite, NULL);
}
