/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** enemies
*/

#include "wolf.h"

static void init_enemy_sound(enemy_t *en)
{
    en->sound = sfSound_create();
    en->sound_buffer =
        sfSoundBuffer_createFromFile("assets/sounds/zombie.wav");
    if (en->sound && en->sound_buffer) {
        sfSound_setBuffer(en->sound, en->sound_buffer);
    }
}

static void init_one_enemy(enemy_t **enemies, int placed)
{
    enemy_t *en = &(*enemies)[placed];

    en->state = E_IDLE;
    en->health = 100;
    en->sprite = set_sprite("assets/sprites/zombie.png",
        &(sfVector2f){0.5f, 0.5f}, NULL, NULL);
    if (en->sprite) {
        en->sprite->rect.left = 0;
        en->sprite->rect.top = 0;
        en->sprite->rect.width = 482;
        en->sprite->rect.height = 601;
    }
    en->attack_cooldown = 0;
    en->scale = 1.0f;
    en->z_offset = 0.5f;
    init_enemy_sound(en);
}

void init_enemies(global_t *glb, enemy_t **enemies, int *enemy_count,
    int **map)
{
    int placed = 0;
    int rx = 0;
    int ry = 0;
    int attempts = 0;

    *enemy_count = MAP_HEIGHT * MAP_WIDTH / 30.0;
    *enemies = malloc(sizeof(enemy_t) * (*enemy_count + 1));
    memset(*enemies, 0, sizeof(enemy_t) * (*enemy_count + 1));
    while (placed < *enemy_count && attempts < 10000) {
        rx = rand() % MAP_WIDTH;
        ry = rand() % MAP_HEIGHT;
        if (map[ry][rx] == 0) {
            (*enemies)[placed].pos = (sfVector2f){(float)rx + 0.5f,
                (float)ry + 0.5f};
            init_one_enemy(enemies, placed);
            placed++;
        }
        attempts++;
    }
    init_daughter(glb, enemies, enemy_count);
}
