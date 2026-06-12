/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** load.h
*/

#ifndef LOAD_H
    #define LOAD_H

    #include "wolf.h"

void init_load(global_t *glb);
void render_load(sfRenderWindow *window, global_t *glb);
scene_t *create_load_scene(void);
void handle_load_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene);
void load_map(global_t *glb);
int check_prerequisite_map(global_t *glb);

#endif
