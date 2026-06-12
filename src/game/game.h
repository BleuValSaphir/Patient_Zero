/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** game
*/

#ifndef INCLUDED_GAME_H
    #define INCLUDED_GAME_H

    #include "items.h"
    #include "player.h"
    #include "enemy.h"
    #include "weapons.h"
    #include "raycasting.h"
    #include "inventory.h"
    #include "shop.h"
    #include "shaders.h"
    #include "map_generation.h"
    #include "particules.h"
    #include "minimap.h"


    #define TYPE glb->game->inventory->indexes[glb->game->inventory->cur_index]

    #define CUR_WEAPON glb->game->weapon[TYPE]
    #define WEAPON glb->game->weapon

    #define INVENTORY glb->game->inventory

    #define WPN_AMMUNATION glb->game->weapon[TYPE].cur_ammunation
    #define INV_AMMUNATION INVENTORY->cur_ammunation[TYPE]

    #define SHOP glb->game->shop

typedef struct shoot_info_s {
    unsigned char cur_weapon_type;
    float shoting_delay;
    float reload_delay;
    bool is_shoting;
    bool reload;
} shoot_info_t;

typedef struct game_s {
    sfRenderTexture *rt;
    struct weapon_s *weapon;
    struct inventory_s *inventory;
    struct items_s items;
    struct shop_s shop;
    shoot_info_t shoot_info;
    sfClock *cooldown;
    sfClock *clock;
    struct enemy_s *enemies;
    float *z_buffer;
    int enemy_count;
    particle_t particles[MAX_PARTICLES];
    struct shaders_s **shader;
    struct vignette_s vignette;
    minimap_t *minimap;
    bool paused;
    bool in_settings;
    struct text_s *pause_title;
    struct text_s *pause_resume;
    struct text_s *pause_settings;
    struct text_s *pause_main_menu;
    struct text_s *save_text;
    sfRectangleShape *pause_bg;
    struct text_s *game_over_title;
    struct text_s *game_over_restart;
    struct text_s *game_over_menu;
    float game_over_fade;
} game_t;

void render_game(sfRenderWindow *window, global_t *glb);
void render_wall_column(global_t *glb, int column,
    float wall_height, float brightness);
void init_game(global_t *glb);
void handle_game_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene);
scene_t *create_game_scene(void);
void update_game(global_t *glb, sfEvent *event);
void render_floor_and_ceiling(sfRenderTexture *rt, global_t *glb);
void handle_game_over_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene);
void render_game_over(sfRenderWindow *window, global_t *glb);

#endif
