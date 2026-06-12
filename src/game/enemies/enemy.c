/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** enemy
*/
#include "wolf.h"

static void sort_ennemies_bubble(global_t *glb, int i)
{
    enemy_t temp = {0};

    for (int j = 0; j < glb->game->enemy_count - i - 1; j++) {
        if (glb->game->enemies[j].distance <
            glb->game->enemies[j + 1].distance) {
            temp = glb->game->enemies[j];
            glb->game->enemies[j] = glb->game->enemies[j + 1];
            glb->game->enemies[j + 1] = temp;
        }
    }
}

void sort_enemies(global_t *glb)
{
    for (int i = 0; i < glb->game->enemy_count; i++) {
        glb->game->enemies[i].distance =
            pow(glb->player.x - glb->game->enemies[i].pos.x, 2) +
            pow(glb->player.y - glb->game->enemies[i].pos.y, 2);
    }
    for (int i = 0; i < glb->game->enemy_count - 1; i++) {
        sort_ennemies_bubble(glb, i);
    }
}

static void draw_enemy_column(global_t *glb, enemy_t *enemy, int x,
    screen_pos_t *screen_pos)
{
    sprite_t *sprite_data = (sprite_t *)enemy->sprite;
    int tex_width;
    int tex_left = sprite_data->rect.left;

    glb->tex_size = sfTexture_getSize(sprite_data->texture);
    tex_width = sprite_data->rect.width > 0 ?
        sprite_data->rect.width : (int)glb->tex_size.x;
    glb->tex_x = (int)(256 * (x - (-glb->screen_width / 2 +
                screen_pos->spr_screnx)) * tex_width /
        glb->screen_width) /
        256;
    if (glb->tex_x < 0)
        glb->tex_x = 0;
    if (glb->tex_x >= tex_width)
        glb->tex_x = tex_width - 1;
    glb->tex_x += tex_left;
    draw_enemy(sprite_data, glb, x, screen_pos);
}

static void brigthness_enemy(enemy_t *enemy, float distance)
{
    float brightness = 255.0f - (distance * 35.0f);

    if (brightness < 0)
        brightness = 0;
    if (brightness > 255)
        brightness = 255;
    sfSprite_setColor(((sprite_t *)enemy->sprite)->sprite,
        sfColor_fromRGBA((sfUint8)brightness, (sfUint8)brightness,
            (sfUint8)brightness, 255));
}

static void render_enemy_columns(global_t *glb, enemy_t *en, float transform_y,
    screen_pos_t *screen_pos)
{
    int draw_start_x = -glb->screen_width / 2 + screen_pos->spr_screnx;
    int draw_end_x = glb->screen_width / 2 + screen_pos->spr_screnx;

    for (int x = draw_start_x; x < draw_end_x; x++) {
        if (x >= 0 && x < SCREEN_WIDTH && transform_y <
            glb->game->z_buffer[x]) {
            draw_enemy_column(glb, en, x, screen_pos);
        }
    }
}

static float get_aspect_ratio(sprite_t *sprite_data)
{
    sfVector2u tex_size = sfTexture_getSize(sprite_data->texture);
    int tex_width = sprite_data->rect.width > 0 ?
        sprite_data->rect.width : (int)tex_size.x;
    int tex_height = sprite_data->rect.height > 0 ?
        sprite_data->rect.height : (int)tex_size.y;

    return (float)tex_width / (float)tex_height;
}

void next_next_render_ennemies(global_t *glb, enemy_t *en,
    float transform_x, float transform_y)
{
    screen_pos_t screen_pos = {0};
    sprite_t *sprite_data = (sprite_t *)en->sprite;
    float aspect_ratio;

    if (!sprite_data || !sprite_data->texture || !sprite_data->sprite)
        return;
    aspect_ratio = get_aspect_ratio(sprite_data);
    glb->base_height = 1920.0f / transform_y;
    screen_pos.spr_screnx = (int)((SCREEN_WIDTH / 2) *
        (1 + transform_x / transform_y));
    screen_pos.screen_height = abs((int)(glb->base_height * en->scale));
    glb->screen_width = abs((int)(screen_pos.screen_height * aspect_ratio));
    if (glb->screen_width <= 0)
        glb->screen_width = 1;
    screen_pos.z_offset = en->z_offset;
    brigthness_enemy(en, transform_y);
    render_enemy_columns(glb, en, transform_y, &screen_pos);
}

static void render_enemys_next(global_t *glb, int i, enemy_pos_t *enemy_pos)
{
    enemy_t *en = &glb->game->enemies[i];
    float sprX = en->pos.x - glb->player.x;
    float sprY = en->pos.y - glb->player.y;
    float invDet = 1.0f / (enemy_pos->planeX * enemy_pos->dirY -
        enemy_pos->dirX * enemy_pos->planeY);
    float transformX = invDet * (enemy_pos->dirY * sprX - enemy_pos->dirX *
        sprY);
    float transformY = invDet * (-enemy_pos->planeY * sprX +
        enemy_pos->planeX * sprY);
    int draw_start_x = 0;
    int draw_end_x = 0;

    if (en->state == E_DEAD)
        return;
    if (transformY <= 0.1f)
        return;
    next_next_render_ennemies(glb, en, transformX, transformY);
}

void render_enemies(global_t *glb)
{
    enemy_pos_t enemy_pos = {0};

    enemy_pos.dirX = cos(glb->player.angle);
    enemy_pos.dirY = sin(glb->player.angle);
    enemy_pos.planeX = -sin(glb->player.angle) * tan(FOV / 2);
    enemy_pos.planeY = cos(glb->player.angle) * tan(FOV / 2);
    sort_enemies(glb);
    for (int i = 0; i < glb->game->enemy_count; i++) {
        render_enemys_next(glb, i, &enemy_pos);
    }
}
