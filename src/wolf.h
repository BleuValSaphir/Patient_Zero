/*
** EPITECH PROJECT, 2026
** mini_wolf
** File description:
** wolf
*/

#ifndef WOLF_H
    #define WOLF_H

    #define SUCCESS 0
    #define ERROR 84

    #define TILE_SIZE 64
    #define MAP_WIDTH glb->map_width
    #define MAP_HEIGHT glb->map_height
    #define SCREEN_WIDTH 1920
    #define SCREEN_HEIGHT 1080
    #define CAMERA_Z 0.5f
    #define PI 3.14159265358979323846
    #define FOV (PI / 3)
    #define NUM_RAYS 1920

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <math.h>
    #include <stdbool.h>
    #include <time.h>
    #include <dirent.h>

typedef enum {
    SCENE_MENU,
    SCENE_MAIN_MENU,
    SCENE_CINEMATIC,
    SCENE_GAME,
    SCENE_PAUSE,
    SCENE_SETTINGS,
    SCENE_LOAD,
    SCENE_SAVE
} scene_type_t;

typedef struct fps_s {
    sfClock *clock;
    sfTime time;
    float second;
    int fps;
    char title[32];
} fps_t;

    #include "player.h"
    #include "map_generation.h"
    #include "hud.h"

typedef struct global_s {
    int map_width;
    int map_height;
    sfClock *render_clock;
    sfTexture *texture;
    sfSprite *sprite;
    sfImage *image;
    sfImage *wall_image;
    sfImage *ceiling_image;
    sfTexture *floor_texture;
    sfTexture *ceiling_texture;
    sfShader *fc_shader;
    sfShader *wall_shader;
    fps_t fps;
    struct sprite_s *init_sprite;
    struct text_s *init_text;
    struct text_s *load_txt;
    struct text_s *settings_txt;
    struct text_s *quit_txt;
    struct text_s *options_txt;
    struct text_s *full_screen_txt;
    struct text_s *audio_txt;
    struct text_s *toggle_txt;
    struct text_s *arrow_left;
    struct text_s *arrow_right;
    struct text_s *vol_display;
    struct text_s *exit_txt;
    struct text_s *sens_txt;
    struct text_s *sens_left;
    struct text_s *sens_right;
    struct text_s *sens_display;
    struct text_s *headbobbing_txt;
    struct text_s *headbobbing_toggle;
    struct text_s *layout_txt;
    struct text_s *layout_toggle;
    struct text_s *fps_txt;
    struct text_s *fps_left;
    struct text_s *fps_right;
    struct text_s *fps_display;
    bool is_qwerty;
    struct text_s *cinematic_txt;
    char target_text[512];
    char current_text[512];
    int text_index;
    sfClock *typewriter_clock;
    sfClock *cinematic_clock;
    int fade_alpha;
    int cinematic_step;
    bool end_cinematic;
    bool start_cinematic;
    bool daughter_caught;
    bool daughter_killed;
    int volume;
    int fps_limit;
    bool is_fullscreen;
    float mouse_sens;
    bool headbobbing;
    struct sprite_s *lighter_sprite;
    bool lighter_active;
    sfClock *lighter_clock;
    struct game_s *game;
    sfVertexArray *wall_array;
    player_t player;
    hud_t *hud;
    sfEvent event;
    sfRenderWindow *window;
    int **map;
    int **copy_map;
    float ratio;
    float base_height;
    int tex_x;
    sfVector2u tex_size;
    int screen_width;
    float dt;
    struct sound_effect_s *menu_sound;
    struct sound_effect_s *goodbye_sound;
    struct sound_effect_s *epilogue_sound;
    struct sound_effect_s *game_music;
    struct input_s *ipt;
    struct text_s *instruction;
    bool valid_file;
} global_t;

typedef struct scene_s {
    void (*init)(global_t *glb);
    void (*handle_events)(global_t *glb, sfEvent *event,
        scene_type_t *next_scene);
    void (*update)(global_t *glb, sfEvent *event);
    void (*draw)(sfRenderWindow *window, global_t *glb);
    void (*destroy)(global_t *glb);
} scene_t;

    #include "game.h"
    #include "main_menu.h"
    #include "raycasting.h"
    #include "menu.h"
    #include "utils.h"
    #include "weapons.h"
    #include "settings.h"
    #include "load.h"
    #include "cinematic.h"
    #include "input.h"
    #include "save.h"

void manage_event(sfRenderWindow *window, scene_type_t *next_scene,
    scene_t *current_scene, global_t *glb);
scene_t *manage_scene(scene_type_t *current_type, scene_type_t next_type,
    scene_t *current_scene, global_t *glb);
void resize_window(global_t *glb, unsigned int width, unsigned int height,
    bool is_fullscreen);
void resize_cond(global_t *glb, bool resize);
#endif
