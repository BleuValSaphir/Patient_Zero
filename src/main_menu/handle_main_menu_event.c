/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** handle_main_menu_event.c
*/

#include "wolf.h"

void handle_main_menu_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene)
{
    if (!glb || !event || !next_scene)
        return;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape) {
        *next_scene = SCENE_MENU;
    }
    if (glb->init_text && is_text_clicked(glb->init_text, event)) {
        *next_scene = SCENE_CINEMATIC;
    }
    if (glb->load_txt && is_text_clicked(glb->load_txt, event)) {
        *next_scene = SCENE_LOAD;
    }
    if (glb->settings_txt && is_text_clicked(glb->settings_txt, event)) {
        *next_scene = SCENE_SETTINGS;
    }
    if (glb->quit_txt && is_text_clicked(glb->quit_txt, event)) {
        sfRenderWindow_close(glb->window);
    }
}
