/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** create_pop_up.C
*/

#include "wolf.h"

void draw_generic_popup(sfRenderWindow *window, sfColor *color,
    sfVector2f *win_size, sfVector2f *pop_up_size)
{
    sfVector2f pos = {
        win_size->x / 2.0f - pop_up_size->x / 2.0f,
        win_size->y / 2.0f - pop_up_size->y / 2.0f
    };
    sfRectangleShape *bg = sfRectangleShape_create();

    sfRectangleShape_setSize(bg, *pop_up_size);
    sfRectangleShape_setFillColor(bg, *color);
    sfRectangleShape_setOutlineColor(bg, sfBlack);
    sfRectangleShape_setOutlineThickness(bg, 2.f);
    sfRectangleShape_setPosition(bg, pos);
    sfRenderWindow_drawRectangleShape(window, bg, NULL);
    sfRectangleShape_destroy(bg);
}
