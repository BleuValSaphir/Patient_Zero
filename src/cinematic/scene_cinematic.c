/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** scene_cinematic.c
*/

#include "wolf.h"

scene_t *create_cinematic_scene(void)
{
    scene_t *scene = malloc(sizeof(scene_t));

    if (!scene)
        return NULL;
    scene->init = init_cinematic;
    scene->handle_events = handle_cinematic_event;
    scene->update = update_cinematic;
    scene->draw = render_cinematic;
    scene->destroy = destroy_cinematic;
    return scene;
}
