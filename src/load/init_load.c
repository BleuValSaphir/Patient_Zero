/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** init_load.c
*/

#include "wolf.h"

void init_load(global_t *glb)
{
    text_info_t info = {"assets/font/Branda-yolq.ttf",
        "\t\t\tLoad Custom Map\n\n\n\n\n\n\n"
        "[ENTER] Confirm     [ESC] Cancel", 45};
    sfVector2f pos = {590.f, 280.f};
    sfVector2f input_pos = {620.f, 485.f};
    sfColor yellow = {255, 255, 0, 255};

    glb->ipt->is_writing = true;
    glb->ipt->cursor = 0;
    glb->ipt->buffer[0] = '\0';
    glb->valid_file = false;
    glb->texture = sfTexture_createFromFile("assets/sprites/main_menu.jpg",
        NULL);
    glb->sprite = sfSprite_create();
    if (glb->texture && glb->sprite)
        sfSprite_setTexture(glb->sprite, glb->texture, sfTrue);
    glb->instruction = set_text(&sfWhite, &pos, &info);
    sfText_setPosition(glb->ipt->text_display, input_pos);
    sfText_setColor(glb->ipt->text_display, yellow);
}
