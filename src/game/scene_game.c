/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** scene_game.c
*/

#include "wolf.h"

scene_t *create_game_scene(void)
{
    scene_t *scene = malloc(sizeof(scene_t));

    if (!scene)
        return NULL;
    scene->init = init_game;
    scene->handle_events = handle_game_event;
    scene->update = update_game;
    scene->draw = render_game;
    scene->destroy = destroy_game;
    return scene;
}
