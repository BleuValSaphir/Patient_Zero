/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** menu_init.c
*/

#include "wolf.h"

void init_menu(global_t *glb)
{
    sfVector2f scale = {5.f, 5.f};
    sfVector2f pos = {0.f, 900.f};

    glb->texture = sfTexture_createFromFile("assets/sprites/"
        "menu.jpg", NULL);
    if (glb->texture)
        sfTexture_setSmooth(glb->texture, sfFalse);
    glb->sprite = sfSprite_create();
    if (glb->texture) {
        sfSprite_setTexture(glb->sprite, glb->texture, sfTrue);
    }
    glb->init_sprite = set_sprite("assets/sprites/enter_sprite.png", &scale,
        NULL, &pos);
    if (glb->init_sprite) {
        glb->init_sprite->rect = (sfIntRect){0, 0, 64, 64};
        sfSprite_setTextureRect(glb->init_sprite->sprite,
            glb->init_sprite->rect);
    }
    glb->goodbye_sound = set_sound("assets/sounds/Goodbye.mp3", 100.0f);
}
