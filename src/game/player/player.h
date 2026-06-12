/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** player.h
*/

#ifndef PLAYER_H
    #define PLAYER_H
    #include "wolf.h"
    #define SPEED 1.0f
    #define ROTATION_SPEED 0.05f

struct global_s;

typedef struct player_s {
    float x;
    float y;
    float angle;
    int tex_x;
    int health;
    int health_max;
    int pitch;
    sfVector2u tex_size;
    sfClock *movement_clock;
    float smooth_dx;
    float smooth_dy;
    float true_pitch;
    float bob_time;
} player_t;

typedef struct range_s {
    float max_dist;
    float dist;
} range_t;

void update_mouse(player_t *player, sfRenderWindow *window,
    struct global_s *glb);
void update_player(struct global_s *glb);
void init_player(player_t *player);
void render_health_bar(sfRenderWindow *window, struct global_s *glb);
void player_shoot(struct global_s *glb);

#endif
