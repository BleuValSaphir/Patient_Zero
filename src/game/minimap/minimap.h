/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** minimap
*/

#ifndef MINIMAP_H
    #define MINIMAP_H
    #define M_RAD 8
    #define M_SIZE 10
    #include "wolf.h"

typedef struct minimap_s {
    sfCircleShape *bg;
    sfRectangleShape *wall;
    sfCircleShape *player;
} minimap_t;

void init_minimap(global_t *glb);
void destroy_minimap(global_t *glb);
void render_minimap(global_t *glb);

#endif /* !MINIMAP_H */
