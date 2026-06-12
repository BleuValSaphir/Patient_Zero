/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** scene_menu.c
*/

#include "wolf.h"

scene_t *create_menu_scene(void)
{
    scene_t *scene = malloc(sizeof(scene_t));

    if (!scene)
        return NULL;
    scene->init = init_menu;
    scene->handle_events = handle_menu_event;
    scene->update = update_menu;
    scene->draw = render_menu;
    scene->destroy = destroy_menu;
    return scene;
}
