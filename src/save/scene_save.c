/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** scene_save.c
*/

#include "wolf.h"

scene_t *create_save_scene(void)
{
    scene_t *scene = malloc(sizeof(scene_t));

    if (!scene)
        return NULL;
    scene->init = init_save;
    scene->handle_events = handle_save_event;
    scene->update = NULL;
    scene->draw = render_load;
    scene->destroy = destroy_save;
    return scene;
}
