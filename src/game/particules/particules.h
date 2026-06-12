/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** particules.h
*/

#ifndef PARTICULE_H
    #define PARTICULE_H
    #define MAX_PARTICLES 100
    #include "wolf.h"

typedef struct particle_s {
    float x;
    float y;
    float vx;
    float vy;
    float life;
    int active;
} particle_t;

void render_particles(global_t *glb);
void spawn_blood(global_t *glb, float x, float y);
void update_particles(global_t *glb);
#endif /* !PARTICULE */
