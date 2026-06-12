/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** destroy_game.c
*/

#include "wolf.h"

void destroy_weapon(weapon_t *weapon)
{
    if (weapon->sprite)
        destroy_sprite(weapon->sprite);
    if (weapon->reload_sprite)
        destroy_sprite(weapon->reload_sprite);
    if (!weapon->sounds)
        return;
    for (int i = 0; i < NB_SOUND; i++)
        destroy_sound(weapon->sounds[i]);
    free(weapon->sounds);
}

void destroy_enemy(enemy_t *enemy)
{
    if (enemy->sprite)
        destroy_sprite(enemy->sprite);
    if (enemy->sound) {
        sfSound_destroy(enemy->sound);
        enemy->sound = NULL;
    }
    if (enemy->sound_buffer) {
        sfSoundBuffer_destroy(enemy->sound_buffer);
        enemy->sound_buffer = NULL;
    }
}

static void destroy_hud_elements(global_t *glb)
{
    if (glb->hud->inv_text)
        destroy_text(glb->hud->inv_text);
    if (glb->hud->munition)
        destroy_sprite(glb->hud->munition);
    if (glb->hud->pistol_sprite)
        destroy_sprite(glb->hud->pistol_sprite);
    if (glb->hud->mp5_sprite)
        destroy_sprite(glb->hud->mp5_sprite);
    free(glb->hud);
}

static void destroy_hud(global_t *glb)
{
    if (!glb->hud)
        return;
    if (glb->hud->health_bg)
        sfRectangleShape_destroy(glb->hud->health_bg);
    if (glb->hud->health_bar)
        sfRectangleShape_destroy(glb->hud->health_bar);
    if (glb->hud->ammo_text)
        destroy_text(glb->hud->ammo_text);
    for (int i = 0; i < 5; i++) {
        if (glb->hud->hotbar_icons[i])
            sfTexture_destroy(glb->hud->hotbar_icons[i]);
    }
    destroy_hud_elements(glb);
}

static void destroy_weapons_and_ennemies(global_t *glb)
{
    if (glb->game->enemies) {
        for (int i = 0; i < glb->game->enemy_count; i++) {
            destroy_enemy(&glb->game->enemies[i]);
        }
        free(glb->game->enemies);
    }
    if (glb->game->weapon) {
        for (int i = 0; i < NB_WEAPON; i++)
            destroy_weapon(&glb->game->weapon[i]);
        free(glb->game->weapon);
    }
    if (glb->player.movement_clock) {
        sfClock_destroy(glb->player.movement_clock);
        glb->player.movement_clock = NULL;
    }
}

static void destroy_textures_and_shaders(global_t *glb)
{
    if (glb->wall_image)
        sfImage_destroy(glb->wall_image);
    if (glb->ceiling_image)
        sfImage_destroy(glb->ceiling_image);
    if (glb->game->rt)
        sfRenderTexture_destroy(glb->game->rt);
    if (glb->floor_texture)
        sfTexture_destroy(glb->floor_texture);
    if (glb->ceiling_texture)
        sfTexture_destroy(glb->ceiling_texture);
    if (glb->fc_shader)
        sfShader_destroy(glb->fc_shader);
    if (glb->wall_shader)
        sfShader_destroy(glb->wall_shader);
    if (glb->texture) {
        sfTexture_destroy(glb->texture);
        glb->texture = NULL;
    }
}

static void free_maps(global_t *glb)
{
    if (glb->map) {
        for (int i = 0; i < MAP_HEIGHT; i++)
            free(glb->map[i]);
        free(glb->map);
        glb->map = NULL;
    }
    /*if (glb->copy_map) {
        for (int i = 0; i < MAP_HEIGHT; i++)
            free(glb->copy_map[i]);
        free(glb->copy_map);
        glb->copy_map = NULL;
    }*/
}

static void destroy_assets(global_t *glb)
{
    if (glb->game->cooldown)
        sfClock_destroy(glb->game->cooldown);
    if (glb->game->z_buffer)
        free(glb->game->z_buffer);
    if (glb->image)
        sfImage_destroy(glb->image);
    destroy_textures_and_shaders(glb);
    if (glb->wall_array)
        sfVertexArray_destroy(glb->wall_array);
    if (glb->lighter_sprite)
        destroy_sprite(glb->lighter_sprite);
    if (glb->lighter_clock)
        sfClock_destroy(glb->lighter_clock);
    free_maps(glb);
}

static void destroy_pause_menu(global_t *glb)
{
    if (glb->game->pause_title)
        destroy_text(glb->game->pause_title);
    if (glb->game->pause_resume)
        destroy_text(glb->game->pause_resume);
    if (glb->game->pause_settings)
        destroy_text(glb->game->pause_settings);
    if (glb->game->pause_main_menu)
        destroy_text(glb->game->pause_main_menu);
    if (glb->game->save_text)
        destroy_text(glb->game->save_text);
    if (glb->game->pause_bg)
        sfRectangleShape_destroy(glb->game->pause_bg);
    if (glb->game->in_settings)
        destroy_settings_texts(glb);
    if (glb->game->game_over_title)
        destroy_text(glb->game->game_over_title);
    if (glb->game->game_over_restart)
        destroy_text(glb->game->game_over_restart);
    if (glb->game->game_over_menu)
        destroy_text(glb->game->game_over_menu);
}

void destroy_game(global_t *glb)
{
    if (!glb->game)
        return;
    destroy_assets(glb);
    if (glb->game->clock)
        sfClock_destroy(glb->game->clock);
    if (glb->game->inventory)
        free(glb->game->inventory);
    destroy_items(&glb->game->items);
    destroy_shop(&SHOP);
    destroy_weapons_and_ennemies(glb);
    destroy_hud(glb);
    destroy_pause_menu(glb);
    destroy_minimap(glb);
    destroy_shaders(glb->game->shader, &glb->game->vignette);
    free(glb->game);
    glb->game = NULL;
}
