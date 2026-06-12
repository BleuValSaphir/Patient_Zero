/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** scene_load.c
*/

#include "wolf.h"

scene_t *create_load_scene(void)
{
    scene_t *scene = malloc(sizeof(scene_t));

    if (!scene)
        return NULL;
    scene->init = init_load;
    scene->handle_events = handle_load_event;
    scene->update = NULL;
    scene->draw = render_load;
    scene->destroy = destroy_load;
    return scene;
}
