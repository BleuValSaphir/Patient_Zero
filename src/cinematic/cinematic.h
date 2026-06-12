/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** cinematic.h
*/

#ifndef CINEMATIC_H
    #define CINEMATIC_H

    #include "wolf.h"
void init_cinematic(global_t *glb);
void render_cinematic(sfRenderWindow *window, global_t *glb);
scene_t *create_cinematic_scene(void);
void handle_cinematic_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene);
void update_cinematic(global_t *glb, sfEvent *event);
#endif
