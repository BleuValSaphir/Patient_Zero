/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** scene_settings.c
*/

#include "wolf.h"

scene_t *create_settings_scene(void)
{
    scene_t *scene = malloc(sizeof(scene_t));

    if (!scene)
        return NULL;
    scene->init = init_settings;
    scene->handle_events = handle_settings_event;
    scene->update = update_settings;
    scene->draw = render_settings;
    scene->destroy = destroy_settings;
    return scene;
}
