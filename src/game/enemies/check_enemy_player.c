/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** check if player is in front of enemy
*/
#include "wolf.h"

bool check_line_of_sight(global_t *glb, sfVector2f *enemy_pos,
    player_t *player, int **map)
{
    float dx = player->x - enemy_pos->x;
    float dy = player->y - enemy_pos->y;
    float distance = sqrt(dx * dx + dy * dy);
    float stepX = distance == 0.0f ? 0 : dx / distance;
    float stepY = distance == 0.0f ? 0 : dy / distance;
    float currentX = enemy_pos->x;
    float currentY = enemy_pos->y;

    if (distance == 0.0f)
        return true;
    for (float i = 0; i < distance; i += 0.1f) {
        currentX += stepX * 0.1f;
        currentY += stepY * 0.1f;
        if (is_wall(glb, (int)currentX, (int)currentY, map))
            return false;
    }
    return true;
}
