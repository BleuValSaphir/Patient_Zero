/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** save
*/

#ifndef SAVE_H
    #define SAVE_H
    #include "wolf.h"

void save_game(global_t *glb, char *save_name);
void handle_save_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene);
void init_save(global_t *glb);
void render_save(sfRenderWindow *window, global_t *glb);
scene_t *create_save_scene(void);
#endif
