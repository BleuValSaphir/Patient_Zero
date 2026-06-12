/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** shooting player
*/

#include "wolf.h"

static float next_shooting(global_t *glb, enemy_t *en,
    float closest_dist)
{
    float hit_tolerance = 0.15f;
    float dx = en->pos.x - glb->player.x;
    float dy = en->pos.y - glb->player.y;
    float dist = sqrt(dx * dx + dy * dy);
    float angle_to_enemy = atan2(dy, dx);
    float diff = 0.0f;

    if (angle_to_enemy < 0)
        angle_to_enemy += 2 * PI;
    diff = fabs(angle_to_enemy - glb->player.angle);
    if (diff > PI)
        diff = 2 * PI - diff;
    if (TYPE == 0)
        hit_tolerance = 0.40f;
    if (diff < hit_tolerance && dist < closest_dist &&
        check_line_of_sight(glb, &en->pos, &glb->player, glb->map)) {
        return dist;
    }
    return closest_dist;
}

range_t *init_range(global_t *glb, range_t *r)
{
    r->dist = 0.0f;
    if (TYPE == 0) {
        r->max_dist = 1.5f;
    } else {
        r->max_dist = 9999.9f;
    }
    return r;
}

static void check_death(global_t *glb, enemy_t *hit_en)
{
    if (hit_en->state == E_DEAD) {
        if (hit_en->attack_cooldown == -100) {
            glb->daughter_killed = true;
            glb->start_cinematic = true;
        } else {
            add_items(&glb->game->items.items_list, hit_en->pos.x,
                hit_en->pos.y, MONEY);
        }
    }
}

static void hit_enemies(global_t *glb, enemy_t *hit_en)
{
    if (hit_en != NULL) {
        hit_en->health -= WEAPON[TYPE].damage;
        spawn_blood(glb, hit_en->pos.x, hit_en->pos.y);
        if (hit_en->health <= 0)
            hit_en->state = E_DEAD;
        check_death(glb, hit_en);
    }
}

void player_shoot(global_t *glb)
{
    enemy_t *hit_en = NULL;
    range_t r;

    if (TYPE == MEDKIT) {
        glb->player.health += 50;
        if (glb->player.health > 100)
            glb->player.health = 100;
        return;
    }
    init_range(glb, &r);
    for (int i = 0; i < glb->game->enemy_count; i++) {
        if (glb->game->enemies[i].state == E_DEAD)
            continue;
        r.dist = next_shooting(glb, &glb->game->enemies[i], r.max_dist);
        if (r.dist < r.max_dist) {
            r.max_dist = r.dist;
            hit_en = &glb->game->enemies[i];
        }
    }
    hit_enemies(glb, hit_en);
}
