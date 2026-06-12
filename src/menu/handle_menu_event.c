/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** handle_menu_event.c
*/

#include "wolf.h"

void handle_menu_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene)
{
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEnter) {
        *next_scene = SCENE_MAIN_MENU;
    }
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape) {
        sfRenderWindow_close(glb->window);
    }
}
