/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** daughter.c
*/

#include "enemy.h"

void init_daughter(global_t *glb, enemy_t **enemies, int *enemy_count)
{
    sprite_t *daughter_spr = NULL;
    int placed = *enemy_count;

    (*enemies)[placed].pos = (sfVector2f){MAP_WIDTH - 3.5f, MAP_HEIGHT - 3.5f};
    (*enemies)[placed].state = E_IDLE;
    daughter_spr = set_sprite("assets/sprites/daughter.png",
        &(sfVector2f){0.3f, 0.3f}, NULL, NULL);
    if (daughter_spr) {
        daughter_spr->rect = (sfIntRect){0, 0, 800 / 7, 234};
        sfSprite_setTextureRect(daughter_spr->sprite, daughter_spr->rect);
    }
    (*enemies)[placed].sprite = daughter_spr;
    (*enemies)[placed].attack_cooldown = -100;
    (*enemies)[placed].scale = 0.7f;
    (*enemies)[placed].z_offset = 0.0f;
    (*enemies)[placed].health = 100000;
    *enemy_count += 1;
}
