/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** enemies
*/

#ifndef ENEMY_H
    #define ENEMY_H
    #include "wolf.h"
    #include "utils.h"

typedef enum {
    E_IDLE,
    E_CHASE,
    E_DEAD
} enemy_state_t;

typedef struct sreen_pos_s {
    int spr_screnx;
    int screen_height;
    float z_offset;
} screen_pos_t;

typedef struct enemy_pos_s {
    float dirX;
    float dirY;
    float planeX;
    float planeY;
} enemy_pos_t;

typedef struct enemy_s {
    sfVector2f pos;
    enemy_state_t state;
    float distance;
    int health;
    struct sprite_s *sprite;
    int attack_cooldown;
    float scale;
    float z_offset;
    sfSound *sound;
    sfSoundBuffer *sound_buffer;
} enemy_t;

void init_enemies(global_t *glb, enemy_t **enemies, int *enemy_count,
    int **map);
void render_enemies(global_t *glb);
bool check_line_of_sight(global_t *glb, sfVector2f *enemy_pos,
    player_t *player, int **map);
void update_enemies(global_t *glb);
void init_daughter(global_t *glb, enemy_t **enemies, int *enemy_count);
void draw_enemy(struct sprite_s *sprite_data, global_t *glb, int x,
    screen_pos_t *screen_pos);
void next_next_render_ennemies(global_t *glb, enemy_t *en,
    float transform_x, float transform_y);

#endif /* !ENEMY_H */
