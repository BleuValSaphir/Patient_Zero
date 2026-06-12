/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** destroy_main_menu.c
*/

#include "wolf.h"

static void destroy_main_menu_texts(global_t *glb)
{
    if (glb->init_text) {
        destroy_text(glb->init_text);
        glb->init_text = NULL;
    }
    if (glb->load_txt) {
        destroy_text(glb->load_txt);
        glb->load_txt = NULL;
    }
    if (glb->settings_txt) {
        destroy_text(glb->settings_txt);
        glb->settings_txt = NULL;
    }
    if (glb->quit_txt) {
        destroy_text(glb->quit_txt);
        glb->quit_txt = NULL;
    }
}

void destroy_main_menu(global_t *glb)
{
    if (!glb)
        return;
    if (glb->texture) {
        sfTexture_destroy(glb->texture);
        glb->texture = NULL;
    }
    if (glb->sprite) {
        sfSprite_destroy(glb->sprite);
        glb->sprite = NULL;
    }
    destroy_main_menu_texts(glb);
    if (glb->epilogue_sound) {
        destroy_sound(glb->epilogue_sound);
        glb->epilogue_sound = NULL;
    }
}
