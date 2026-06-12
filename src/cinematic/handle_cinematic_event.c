/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** handle_cinematic_event.c
*/

#include "wolf.h"

void handle_cinematic_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene)
{
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
        *next_scene = SCENE_MAIN_MENU;
    if (event->type == sfEvtKeyPressed && (event->key.code == sfKeySpace
            || event->key.code == sfKeyEnter))
        glb->end_cinematic = true;
}
