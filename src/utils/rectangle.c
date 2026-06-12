/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** rectangle
*/

#include "wolf.h"

sfRectangleShape *set_rectangle(sfVector2f *size, sfColor *color,
    sfVector2f *pos)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setSize(rect, *size);
    sfRectangleShape_setFillColor(rect, *color);
    sfRectangleShape_setOrigin(rect, (sfVector2f){(*size).x / 2,
            (*size).y / 2});
    sfRectangleShape_setPosition(rect, *pos);
    return rect;
}
