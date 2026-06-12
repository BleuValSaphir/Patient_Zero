/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** hud.h
*/

#ifndef HUD_H
    #define HUD_H

    #include "wolf.h"

struct global_s;

typedef struct hud_s {
    sfRectangleShape *health_bar;
    sfRectangleShape *health_bg;
    struct text_s *ammo_text;
    struct text_s *inv_text;
    struct sprite_s *munition;
    struct sprite_s *pistol_sprite;
    struct sprite_s *mp5_sprite;
    float display_timer;
    bool is_visible;
    int last_health;
    sfVector2f center;
    float radius;
    int current_ammo;
    int max_ammo;
    float angle_deg;
    float angle_rad;
    float x;
    float y;
    float start_angle;
    float total_angle;
    float angle_step;
    int last_weapon_index;
    sfTexture *hotbar_icons[5];
} hud_t;

void init_hud(struct global_s *glb);
void update_hud(struct global_s *glb, bool action_triggered);
void render_hud(sfRenderWindow *window, struct global_s *glb);

#endif
