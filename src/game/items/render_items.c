/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** render_items.c
*/

#include "items.h"


static void render_single_item(global_t *glb, items_list_t *tmp,
    enemy_pos_t *cam)
{
    enemy_t en = {0};
    float sprX = tmp->pos.x - glb->player.x;
    float sprY = tmp->pos.y - glb->player.y;
    float invDet = 1.0f / (cam->planeX * cam->dirY - cam->dirX * cam->planeY);
    float transformX = invDet * (cam->dirY * sprX - cam->dirX * sprY);
    float transformY = invDet * (-cam->planeY * sprX + cam->planeX * sprY);

    en.pos = tmp->pos;
    if (tmp->type == MONEY) {
        en.sprite = glb->game->items.sprite;
        en.scale = 0.05f;
    } else {
        en.sprite = glb->game->items.sprite_health;
        en.scale = 0.3f;
    }
    en.z_offset = 0.2f;
    if (transformY > 0.3f)
        next_next_render_ennemies(glb, &en, transformX, transformY);
}

void render_items_sprites(global_t *glb)
{
    enemy_pos_t cam = {0};
    items_list_t *tmp = glb->game->items.items_list;

    cam.dirX = cos(glb->player.angle);
    cam.dirY = sin(glb->player.angle);
    cam.planeX = -sin(glb->player.angle) * tan(FOV / 2);
    cam.planeY = cos(glb->player.angle) * tan(FOV / 2);
    while (tmp) {
        render_single_item(glb, tmp, &cam);
        tmp = tmp->next;
    }
}

void render_items(global_t *glb)
{
    if (glb->game->items.is_item == true)
        sfRenderWindow_drawText(glb->window, glb->game->items.text->text,
            NULL);
}
