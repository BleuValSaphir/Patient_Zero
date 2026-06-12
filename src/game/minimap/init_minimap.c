/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** minimap
*/

#include "wolf.h"

void destroy_minimap(global_t *glb)
{
    if (!glb || !glb->game || !glb->game->minimap)
        return;
    sfCircleShape_destroy(glb->game->minimap->bg);
    sfRectangleShape_destroy(glb->game->minimap->wall);
    sfCircleShape_destroy(glb->game->minimap->player);
    free(glb->game->minimap);
}

void init_minimap(global_t *glb)
{
    glb->game->minimap = malloc(sizeof(minimap_t));
    if (!glb->game->minimap)
        return;
    glb->game->minimap->bg = sfCircleShape_create();
    glb->game->minimap->wall = sfRectangleShape_create();
    glb->game->minimap->player = sfCircleShape_create();
}
