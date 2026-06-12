/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** handle_load_event.c
*/

#include "input.h"

void handle_load_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene)
{
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
        *next_scene = SCENE_MAIN_MENU;
    if (glb->ipt->is_writing == false) {
        strcat(glb->ipt->buffer, ".save");
        load_map(glb);
        if (glb->valid_file)
            *next_scene = SCENE_CINEMATIC;
        else
            *next_scene = SCENE_MAIN_MENU;
        glb->ipt->is_writing = true;
    }
    if (input_function(glb, event) == true)
        return;
    sfText_setString(glb->ipt->text_display, glb->ipt->buffer);
}
