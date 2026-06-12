/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** main_menu
*/

#ifndef MAIN_MENU_H
    #define MAIN_MENU_H

    #include "wolf.h"

void render_main_menu(sfRenderWindow *window, global_t *glb);
void init_main_menu(global_t *glb);
void handle_main_menu_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene);
scene_t *create_main_menu_scene(void);
void update_main_menu(global_t *glb, sfEvent *event);

#endif
