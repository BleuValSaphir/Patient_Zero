/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** scene_main_menu.c
*/

#include "wolf.h"

scene_t *create_main_menu_scene(void)
{
    scene_t *scene = malloc(sizeof(scene_t));

    if (!scene)
        return NULL;
    scene->init = init_main_menu;
    scene->handle_events = handle_main_menu_event;
    scene->update = update_main_menu;
    scene->draw = render_main_menu;
    scene->destroy = destroy_main_menu;
    return scene;
}
