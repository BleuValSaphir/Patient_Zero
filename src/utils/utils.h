/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** utils.h
*/

#ifndef UTILS_H
    #define UTILS_H

    #include "wolf.h"

typedef struct sprite_s {
    sfSprite *sprite;
    sfTexture *texture;
    sfClock *clock;
    sfIntRect rect;
} sprite_t;

typedef struct text_s {
    sfFont *font;
    sfText *text;
} text_t;

typedef struct text_info_s {
    char *filepath;
    char *str;
    unsigned int size;
} text_info_t;

typedef struct sound_effect_s {
    sfSoundBuffer *buff;
    sfSound *sound;
    bool played;
    float delay;
} sound_effect_t;

typedef struct my_clock_s {
    sfClock *clock;
    float second;
} my_clock_t;

sound_effect_t *set_sound(char *filepath, float volume);
void destroy_sound(sound_effect_t *sound);
sprite_t *set_sprite(char *filepath, const sfVector2f *scale,
    const sfVector2f *origin, const sfVector2f *pos);
text_t *set_text(sfColor *color, const sfVector2f *pos, text_info_t *inf);
sfCircleShape *set_circle(float radius, sfVector2f *pos,
    sfColor *icolor, sfColor *ocolor);
sfRectangleShape *set_rectangle(sfVector2f *size, sfColor *color,
    sfVector2f *pos);
void handle_hover_anim(sfRenderWindow *window, text_t *txt);
bool is_text_clicked(text_t *txt, sfEvent *event);
void destroy_sprite(sprite_t *sprite);
void destroy_menu(global_t *glb);
void destroy_main_menu(global_t *glb);
void destroy_game(global_t *glb);
void destroy_text(text_t *txt);
void destroy_settings(global_t *glb);
void destroy_cinematic(global_t *glb);
void destroy_load(global_t *glb);
void destroy_save(global_t *glb);
int manage_env(char **env);
void print_usage(void);
int check_args(int ac, char **av);
void draw_generic_popup(sfRenderWindow *window, sfColor *color,
    sfVector2f *win_size, sfVector2f *pop_up_size);
void handle_color_anim(sfRenderWindow *window, text_t *txt);
void destroy_all(global_t *glb);
sfRenderWindow *create_window(bool is_fullscreen);

#endif
