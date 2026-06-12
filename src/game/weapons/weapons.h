/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** weapons
*/

#ifndef WEAPONS_H
    #define WEAPONS_H

    #define NB_SOUND 3
    #define SHOOT 0
    #define RELOAD 1
    #define DRY_FIRE 2

    #include "wolf.h"

    #define NB_WEAPON 5
    #define KNIFE 0
    #define GUN 1
    #define MP5 2
    #define SPECIAL 3
    #define MEDKIT 4


typedef struct preset_weapon_s {
    unsigned char weapon_type;
    char *name;
    int damage;
    float mass_factor;
    int max_ammunation;
    float shoting_delay;
    int reload_delay;
    char *texture_file;
    char *reload_texture_file;
    sfVector2f scale;
    sfVector2f pos;
    int rect_width;
    int rect_height;
    int rect_offset;
    int rect_max_offset;
    int reload_rect_width;
    int reload_rect_height;
    int dry_jump;
    float speed_rect;
    char *shoot_sound_file;
    float shoot_volume;
    char *reload_sound_file;
    float reload_volume;
    char *dry_fire_soud_file;
    float dry_fire_volume;
} preset_weapon_t;

static const preset_weapon_t wps[] = {
    {KNIFE, "knife", 50, 0.05f, 0, 0.3, 0,
        "assets/sprites/knife_anim.png", NULL,
        {1.f, 1.f}, {0.30, 0.72}, 714, 315, 714, 4998, 0, 0, 0, 0.1,
        "assets/sounds/knife.wav", 100., "assets/sounds/knife.wav", 100.,
        "assets/sounds/knife.wav", 100.},
    {GUN, "gun", 70, 0.04f, 12, 0.4, 1, "assets/sprites/pistol.png",
        "assets/sprites/pistol_reload.png", {1.5f, 1.5f},
        {0.30, 0.73}, 599, 245, 599, 2994, 599, 245, 0, 0.2,
        "assets/sounds/pistol.mp3", 70.,
        "assets/sounds/pistol_reload.mp3", 100.,
        "assets/sounds/shotgun_dry_fire.mp3", 100.},
    {MP5, "mp5", 35, 0.03f, 20, 0.02, 1, "assets/sprites/MP.png",
        "assets/sprites/MP_reload.png", {0.5, 0.5},
        {0.24, 0.80}, 1912, 772, 1912, 3824, 1250, 545, 0, 0.01,
        "assets/sounds/Mp5.wav",
        70., "assets/sounds/Mp5_reload.wav", 100.,
        "assets/sounds/shotgun_dry_fire.mp3", 100.},
    {SPECIAL, "special", 1000000, 0.05, 0, 0.5, 0, "assets/sprites/special.png",
        NULL, {1.5, 1.5}, {0.54, 0.69}, 120, 222, 120, 480, 0, 0, 0, 0.1,
        "assets/sounds/miaou.mp3", 70., "assets/sounds/miaou.mp3", 100.,
        "assets/sounds/shotgun_dry_fire.mp3", 100.},
    {MEDKIT, "medkit", 0, 0.05f, 0, 0.3, 0, "assets/sprites/heal.png",
        NULL, {2.0f, 2.0f}, {0.24, 0.73}, 479, 214, 479, 3838, 0, 0, 0, 0.15,
        "assets/sounds/pick-up.mp3", 100., "assets/sounds/pick-up.mp3", 100.,
        "assets/sounds/pick-up.mp3", 100.},
    {0, 0, 0}
};

typedef struct weapon_s {
    char *name;
    int damage;
    float mass_factor;
    int cur_ammunation;
    int max_ammunation;
    float shoting_delay;
    int reload_delay;
    int rect_offset;
    int rect_max_offset;
    int dry_jump;
    float speed_rect;
    struct sprite_s *sprite;
    struct sprite_s *reload_sprite;
    struct sound_effect_s **sounds;
    sfVector2f pos;
} weapon_t;

int init_weapons(sfRenderWindow *window, weapon_t **weapon);
void update_weapon_actions(global_t *glb);

#endif
