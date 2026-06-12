/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** raycasting.c
*/

#include "wolf.h"

int is_wall(global_t *glb, int x, int y, int **map)
{
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
        return 1;
    return map[y][x] == 1;
}

static void get_side_y(distance_t *dist, player_t *player)
{
    if (dist->ray_dir_y < 0) {
        dist->step_y = -1;
        dist->side_dist_y = (player->y - dist->map_y) *
            dist->delta_dist_y;
    } else {
        dist->step_y = 1;
        dist->side_dist_y = (dist->map_y + 1.0f - player->y) *
            dist->delta_dist_y;
    }
}

static void get_side_x(distance_t *dist, player_t *player)
{
    if (dist->ray_dir_x < 0) {
        dist->step_x = -1;
        dist->side_dist_x = (player->x - dist->map_x) *
            dist->delta_dist_x;
    } else {
        dist->step_x = 1;
        dist->side_dist_x = (dist->map_x + 1.0f - player->x) *
            dist->delta_dist_x;
    }
}

void get_step_side_dsit(player_t *player, distance_t *dist)
{
    if (dist->ray_dir_x == 0)
        dist->delta_dist_x = 1e30f;
    else
        dist->delta_dist_x = fabs(1.0f / dist->ray_dir_x);
    if (dist->ray_dir_y == 0)
        dist->delta_dist_y = 1e30f;
    else
        dist->delta_dist_y = fabs(1.0f / dist->ray_dir_y);
    get_side_x(dist, player);
    get_side_y(dist, player);
}

void manage_dist_hit(global_t *glb, distance_t *dist,
    int **map, float *fish_eye)
{
    while (dist->hit == 0) {
        if (dist->side_dist_x < dist->side_dist_y) {
            dist->side_dist_x += dist->delta_dist_x;
            dist->map_x += dist->step_x;
            dist->side = 0;
        } else {
            dist->side_dist_y += dist->delta_dist_y;
            dist->map_y += dist->step_y;
            dist->side = 1;
        }
        if (is_wall(glb, dist->map_x, dist->map_y, map))
            dist->hit = 1;
    }
    if (dist->side == 0)
        *fish_eye = (dist->map_x - glb->player.x + (1 - dist->step_x) / 2.0f) /
            dist->ray_dir_x;
    else
        *fish_eye = (dist->map_y - glb->player.y + (1 - dist->step_y) / 2.0f) /
            dist->ray_dir_y;
}

static void check_dist_side(distance_t *dist, player_t *player, float *fish_eye)
{
    float wall_x;

    if (dist->side == 0)
        wall_x = player->y + *fish_eye * dist->ray_dir_y;
    else
        wall_x = player->x + *fish_eye * dist->ray_dir_x;
    wall_x -= floor(wall_x);
    player->tex_x = (int)(wall_x * (float)player->tex_size.x);
    if (dist->side == 0 && dist->ray_dir_x > 0)
        player->tex_x = player->tex_size.x - player->tex_x - 1;
    if (dist->side == 1 && dist->ray_dir_y < 0)
        player->tex_x = player->tex_size.x - player->tex_x - 1;
}

float cast_single_ray(global_t *glb, float ray_angle, sfRenderTexture *rt,
    int **map)
{
    distance_t dist = {0};
    float fish_eye;

    dist.ray_dir_x = cos(ray_angle);
    dist.ray_dir_y = sin(ray_angle);
    dist.map_x = (int)glb->player.x;
    dist.map_y = (int)glb->player.y;
    get_step_side_dsit(&glb->player, &dist);
    manage_dist_hit(glb, &dist, map, &fish_eye);
    check_dist_side(&dist, &glb->player, &fish_eye);
    fish_eye *= cos(ray_angle - glb->player.angle);
    return fish_eye;
}

static void handle_wall_properties(float distance, float *height, float *bright)
{
    if (distance < 0.1f)
        distance = 0.1f;
    *height = (TILE_SIZE / distance) * 30.0f;
    *bright = 255.0f - (distance * 35.0f);
    if (*bright < 0)
        *bright = 0;
    if (*bright > 255)
        *bright = 255;
}

static void angle_next(global_t *glb, sfRenderTexture *rt, int i)
{
    float start_angle = glb->player.angle - (FOV / 2);
    float step = FOV / (float)NUM_RAYS;
    float ray_angle = 0.0f;
    float dist_walls = 0.0f;
    float brightness;
    float wall_height;

    ray_angle = start_angle + (i * step);
    dist_walls = cast_single_ray(glb, ray_angle, rt, glb->map);
    if (i < SCREEN_WIDTH)
        glb->game->z_buffer[i] = dist_walls;
    handle_wall_properties(dist_walls, &wall_height, &brightness);
    render_wall_column(glb, i, wall_height, brightness);
}

void cast_all_rays(sfRenderTexture *rt, global_t *glb)
{
    sfRenderStates states;

    glb->player.tex_size = sfImage_getSize(glb->wall_image);
    for (int i = 0; i < NUM_RAYS; i++) {
        angle_next(glb, rt, i);
    }
    states.blendMode = sfBlendAlpha;
    states.transform = sfTransform_Identity;
    states.texture = glb->texture;
    states.shader = NULL;
    sfRenderTexture_drawVertexArray(rt, glb->wall_array, &states);
}
