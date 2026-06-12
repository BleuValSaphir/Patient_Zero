/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** raycasting.h
*/

#ifndef RAYCASTING_H
    #define RAYCASTING_H

typedef struct distance_s {
    float ray_dir_x;
    float ray_dir_y;
    float delta_dist_x;
    float delta_dist_y;
    float side_dist_x;
    float side_dist_y;
    int step_x;
    int step_y;
    int map_x;
    int map_y;
    int hit;
    int side;
} distance_t;

void cast_all_rays(sfRenderTexture *rt, global_t *glb);
float cast_single_ray(global_t *glb, float ray_angle,
    sfRenderTexture *rt, int **map);
int is_wall(global_t *glb, int x, int y, int **map);

#endif
