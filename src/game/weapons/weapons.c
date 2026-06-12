/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** weapons
*/

#include "weapons.h"

static int init_shooting_var(weapon_t **weapon, char type)
{
    if (!*weapon)
        return ERROR;
    (*weapon)[type].name = wps[type].name;
    (*weapon)[type].damage = wps[type].damage;
    (*weapon)[type].mass_factor = wps[type].mass_factor;
    (*weapon)[type].cur_ammunation = 0;
    (*weapon)[type].max_ammunation = wps[type].max_ammunation;
    (*weapon)[type].shoting_delay = wps[type].shoting_delay;
    (*weapon)[type].reload_delay = wps[type].reload_delay;
    return SUCCESS;
}

static void init_rect(weapon_t **weapon, char type)
{
    (*weapon)[type].sprite->rect.height = wps[type].rect_height;
    (*weapon)[type].sprite->rect.width = wps[type].rect_width;
    (*weapon)[type].rect_offset = wps[type].rect_offset;
    (*weapon)[type].rect_max_offset = wps[type].rect_max_offset;
    (*weapon)[type].dry_jump = wps[type].dry_jump;
    (*weapon)[type].speed_rect = wps[type].speed_rect;
    sfSprite_setTextureRect((*weapon)[type].sprite->sprite,
        (*weapon)[type].sprite->rect);
}

static int init_sounds(weapon_t **weapon, char type)
{
    (*weapon)[type].sounds = malloc(sizeof(sound_effect_t *) * NB_SOUND);
    if (!(*weapon)[type].sounds)
        return ERROR;
    (*weapon)[type].sounds[SHOOT] = set_sound(wps[type].shoot_sound_file,
        wps[type].shoot_volume);
    (*weapon)[type].sounds[RELOAD] = set_sound(wps[type].reload_sound_file,
        wps[type].reload_volume);
    (*weapon)[type].sounds[DRY_FIRE] = set_sound(wps[type].dry_fire_soud_file,
        wps[type].dry_fire_volume);
    return SUCCESS;
}

static void init_reload_sprite(weapon_t **weapon, char type, sfVector2f *pos)
{
    if (wps[type].reload_texture_file) {
        (*weapon)[type].reload_sprite =
            set_sprite(wps[type].reload_texture_file,
            &wps[type].scale, NULL, pos);
        if ((*weapon)[type].reload_sprite) {
            (*weapon)[type].reload_sprite->rect.width =
                wps[type].reload_rect_width;
            (*weapon)[type].reload_sprite->rect.height =
                wps[type].reload_rect_height;
            (*weapon)[type].reload_sprite->rect.left = 0;
            (*weapon)[type].reload_sprite->rect.top = 0;
            sfSprite_setTextureRect((*weapon)[type].reload_sprite->sprite,
                (*weapon)[type].reload_sprite->rect);
        }
    } else
        (*weapon)[type].reload_sprite = NULL;
}

int init_weapons(sfRenderWindow *window, weapon_t **weapon)
{
    *weapon = malloc(sizeof(weapon_t) * NB_WEAPON);
    if (!*weapon)
        return ERROR;
    memset(*weapon, 0, sizeof(weapon_t) * NB_WEAPON);
    for (int type = 0; type < NB_WEAPON; type++) {
        (*weapon)[type].pos = (sfVector2f){
            .x = wps[type].pos.x * SCREEN_WIDTH,
            .y = wps[type].pos.y * SCREEN_HEIGHT};
        if (init_shooting_var(weapon, type) == ERROR)
            return ERROR;
        (*weapon)[type].sprite = set_sprite(wps[type].texture_file,
            &wps[type].scale, NULL, &(*weapon)[type].pos);
        if (!(*weapon)[type].sprite)
            return ERROR;
        init_rect(weapon, type);
        if (init_sounds(weapon, type) == ERROR)
            return ERROR;
        init_reload_sprite(weapon, type, &(*weapon)[type].pos);
    }
    return SUCCESS;
}
