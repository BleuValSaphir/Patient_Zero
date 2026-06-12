/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** main_menu.c
*/

#include "wolf.h"

void render_main_menu(sfRenderWindow *window, global_t *glb)
{
    if (glb->sprite) {
        sfRenderWindow_drawSprite(window, glb->sprite, NULL);
    }
    if (glb->init_text)
        sfRenderWindow_drawText(window, glb->init_text->text, NULL);
    if (glb->load_txt)
        sfRenderWindow_drawText(window, glb->load_txt->text, NULL);
    if (glb->settings_txt)
        sfRenderWindow_drawText(window, glb->settings_txt->text, NULL);
    if (glb->quit_txt)
        sfRenderWindow_drawText(window, glb->quit_txt->text, NULL);
}
