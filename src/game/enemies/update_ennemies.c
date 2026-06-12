/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** update ennemies
*/

#include "wolf.h"

static void update_attack_ennemy(global_t *glb, float dist, enemy_t *en)
{
    if (dist < 0.5f) {
        if (en->attack_cooldown == -100) {
            glb->player.health = 0;
            return;
        }
        if (en->attack_cooldown <= 0) {
            glb->player.health -= 10;
            en->attack_cooldown = 160;
            glb->game->vignette.is_getting_hit = true;
            glb->game->vignette.is_increasing = true;
        }
    }
}

static void check_cinematic_trigger(global_t *glb, enemy_t *en, float dist)
{
    if (en->attack_cooldown == -100 && dist <= 0.8f) {
        glb->start_cinematic = true;
        glb->daughter_caught = true;
        glb->fade_alpha = 255;
    }
}

static void apply_separation(global_t *glb, enemy_t *en, float *mX,
    float *mY)
{
    enemy_t *oth;
    float dx;
    float dy;
    float dist;

    for (int i = 0; i < glb->game->enemy_count; i++) {
        oth = &glb->game->enemies[i];
        if (oth == en || oth->state == E_DEAD)
            continue;
        dx = en->pos.x - oth->pos.x;
        dy = en->pos.y - oth->pos.y;
        dist = sqrt(dx * dx + dy * dy);
        if (dist > 0.001f && dist < 0.6f) {
            *mX += (dx / dist) * 2.5f * glb->dt;
            *mY += (dy / dist) * 2.5f * glb->dt;
        }
    }
}

static void move_enemy(global_t *glb, enemy_t *en, float mX, float mY)
{
    float pX = 0.0f;
    float pY = 0.0f;

    if (mX != 0.0f)
        pX = (mX > 0.0f) ? 0.4f : -0.4f;
    if (mY != 0.0f)
        pY = (mY > 0.0f) ? 0.4f : -0.4f;
    if (!is_wall(glb, (int)(en->pos.x + mX + pX), (int)en->pos.y, glb->map))
        en->pos.x += mX;
    if (!is_wall(glb, (int)en->pos.x, (int)(en->pos.y + mY + pY), glb->map))
        en->pos.y += mY;
}

static void play_enemy_sound(enemy_t *en, float dist)
{
    if (dist < 3.0f && en->sound) {
        if (sfSound_getStatus(en->sound) != sfPlaying) {
            sfSound_play(en->sound);
        }
    }
}

static void update_next_enemys(global_t *glb, enemy_t *en, float speed)
{
    float dx = glb->player.x - en->pos.x;
    float dy = glb->player.y - en->pos.y;
    float dist = sqrt(dx * dx + dy * dy);
    float moveX = 0.0f;
    float moveY = 0.0f;

    check_cinematic_trigger(glb, en, dist);
    play_enemy_sound(en, dist);
    if (dist > 0.5f) {
        moveX = (dx / dist) * speed;
        moveY = (dy / dist) * speed;
        apply_separation(glb, en, &moveX, &moveY);
        move_enemy(glb, en, moveX, moveY);
    }
    update_attack_ennemy(glb, dist, en);
}

static void update_enemy_sprite(enemy_t *en)
{
    sfTime time;

    if (!en->sprite || en->sprite->rect.width <= 0 ||
        !en->sprite->clock || !en->sprite->texture)
        return;
    time = sfClock_getElapsedTime(en->sprite->clock);
    if (sfTime_asSeconds(time) > 0.30f) {
        en->sprite->rect.left += en->sprite->rect.width;
        if ((unsigned int)en->sprite->rect.left + en->sprite->rect.width
            >= sfTexture_getSize(en->sprite->texture).x) {
            en->sprite->rect.left = 0;
        }
        sfClock_restart(en->sprite->clock);
    }
}

void update_enemies(global_t *glb)
{
    float speed = 0.5f * glb->dt;
    enemy_t *en = NULL;
    bool sees_player = false;

    for (int i = 0; i < glb->game->enemy_count; i++) {
        en = &glb->game->enemies[i];
        if (en->state == E_DEAD)
            continue;
        update_enemy_sprite(en);
        if (en->attack_cooldown > 0)
            en->attack_cooldown--;
        sees_player = check_line_of_sight(glb, &en->pos, &glb->player,
            glb->map);
        if (en->attack_cooldown == -100 && en->state == E_CHASE)
            sees_player = true;
        en->state = sees_player ? E_CHASE : E_IDLE;
        if (en->state == E_CHASE)
            update_next_enemys(glb, en,
                en->attack_cooldown == -100 ? 0.6f * glb->dt : speed);
    }
}
