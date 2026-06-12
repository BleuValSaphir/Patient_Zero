/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** render_load.c
*/

#include "wolf.h"

static void render_input_box(sfRenderWindow *window)
{
    sfRectangleShape *input_box = sfRectangleShape_create();

    sfRectangleShape_setSize(input_box, (sfVector2f){700.f, 60.f});
    sfRectangleShape_setFillColor(input_box, (sfColor){50, 50, 50, 255});
    sfRectangleShape_setOutlineThickness(input_box, 0.f);
    sfRectangleShape_setOutlineColor(input_box, sfWhite);
    sfRectangleShape_setPosition(input_box, (sfVector2f){610.f, 480.f});
    sfRenderWindow_drawRectangleShape(window, input_box, NULL);
    sfRectangleShape_destroy(input_box);
}

void render_load(sfRenderWindow *window, global_t *glb)
{
    char display_str[256] = {0};
    int ms = 0;

    if (glb->sprite)
        sfRenderWindow_drawSprite(window, glb->sprite, NULL);
    draw_generic_popup(window, &(sfColor){0, 0, 0, 200},
        &(sfVector2f){1920.f, 1080.f}, &(sfVector2f){800.f, 600.f});
    if (glb->instruction)
        sfRenderWindow_drawText(window, glb->instruction->text, NULL);
    render_input_box(window);
    if (glb->ipt && glb->ipt->text_display) {
        strcpy(display_str, glb->ipt->buffer);
        ms = sfTime_asMilliseconds(sfClock_getElapsedTime(glb->fps.clock));
        if ((ms % 1000) > 500 && glb->ipt->is_writing)
            strcat(display_str, "_");
        sfText_setString(glb->ipt->text_display, display_str);
        sfRenderWindow_drawText(glb->window, glb->ipt->text_display, NULL);
    }
}
