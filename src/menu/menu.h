/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** menu
*/

#ifndef MENU_H
    #define MENU_H
    #include "wolf.h"

void render_menu(sfRenderWindow *window, global_t *glb);
void init_menu(global_t *glb);
void handle_menu_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene);
scene_t *create_menu_scene(void);
void update_menu(global_t *glb, sfEvent *event);

#endif
