/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** settings.h
*/

#ifndef SETTING_H
    #define SETTING_H

    #include "wolf.h"

void init_settings(global_t *glb);
void render_settings(sfRenderWindow *window, global_t *glb);
void init_settings_texts(global_t *glb);
void destroy_settings_texts(global_t *glb);
void render_settings_texts(sfRenderWindow *window, global_t *glb);
void handle_settings_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene);
scene_t *create_settings_scene(void);
void update_settings(global_t *glb, sfEvent *event);
void save_settings(global_t *glb);
void load_settings(global_t *glb);

#endif
