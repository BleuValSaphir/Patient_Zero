/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** game.c
*/

#include "wolf.h"

void create_fade(global_t *glb, sfRenderWindow *window)
{
    sfRectangleShape *rect;

    if (glb->fade_alpha > 0) {
        rect = sfRectangleShape_create();
        sfRectangleShape_setSize(rect, (sfVector2f){1920.f, 1080.f});
        sfRectangleShape_setFillColor(rect,
            (sfColor){0, 0, 0, glb->fade_alpha});
        sfRenderWindow_drawRectangleShape(window, rect, NULL);
        sfRectangleShape_destroy(rect);
    }
}

void render_shooting(global_t *glb)
{
    if (glb->game->shoot_info.reload && glb->game->weapon[TYPE].reload_sprite) {
        sfSprite_setTextureRect(glb->game->weapon[TYPE].reload_sprite->sprite,
            glb->game->weapon[TYPE].reload_sprite->rect);
        sfRenderTexture_drawSprite(glb->game->rt,
            glb->game->weapon[TYPE].reload_sprite->sprite, NULL);
    } else if (glb->game->weapon[TYPE].sprite) {
        sfSprite_setTextureRect(glb->game->weapon[TYPE].sprite->sprite,
            glb->game->weapon[TYPE].sprite->rect);
        sfRenderTexture_drawSprite(glb->game->rt,
            glb->game->weapon[TYPE].sprite->sprite, NULL);
    }
}

static void render_pause_menu(sfRenderWindow *window, global_t *glb)
{
    sfRenderWindow_drawRectangleShape(window, glb->game->pause_bg, NULL);
    if (glb->game->in_settings) {
        render_settings_texts(window, glb);
    } else {
        sfRenderWindow_drawText(window, glb->game->pause_title->text, NULL);
        sfRenderWindow_drawText(window, glb->game->pause_resume->text, NULL);
        sfRenderWindow_drawText(window, glb->game->pause_settings->text, NULL);
        sfRenderWindow_drawText(window, glb->game->pause_main_menu->text, NULL);
        sfRenderWindow_drawText(window, glb->game->save_text->text, NULL);
    }
}

static void draw_crosshair(sfRenderWindow *window)
{
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setRadius(circle, 3.0f);
    sfCircleShape_setFillColor(circle, sfColor_fromRGBA(255, 255, 255, 200));
    sfCircleShape_setOrigin(circle, (sfVector2f){3.0f, 3.0f});
    sfCircleShape_setPosition(circle,
        (sfVector2f){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f});
    sfRenderWindow_drawCircleShape(window, circle, NULL);
    sfCircleShape_destroy(circle);
}

static void render_3d_scene(global_t *glb)
{
    sfRenderTexture_clear(glb->game->rt, sfWhite);
    render_floor_and_ceiling(glb->game->rt, glb);
    cast_all_rays(glb->game->rt, glb);
    render_items_sprites(glb);
    render_enemies(glb);
    render_particles(glb);
    if (glb->lighter_active && glb->lighter_sprite) {
        sfRenderTexture_drawSprite(glb->game->rt,
            glb->lighter_sprite->sprite, NULL);
    } else {
        render_shooting(glb);
    }
    sfRenderTexture_display(glb->game->rt);
}

void render_game(sfRenderWindow *window, global_t *glb)
{
    if (!glb || !glb->game)
        return;
    if (!glb->game->paused)
        render_3d_scene(glb);
    render_shaders(window, glb);
    if (glb->player.health <= 0) {
        render_game_over(window, glb);
        return;
    }
    if (!glb->game->paused) {
        render_hud(window, glb);
        render_minimap(glb);
        render_items(glb);
        render_shop(window, &glb->game->shop);
        if (!glb->lighter_active)
            draw_crosshair(window);
        create_fade(glb, window);
    }
    if (glb->game->paused)
        render_pause_menu(window, glb);
}
