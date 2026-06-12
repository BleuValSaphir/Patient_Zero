/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** circle
*/

#include "wolf.h"

sfCircleShape *set_circle(float radius, sfVector2f *pos,
    sfColor *icolor, sfColor *ocolor)
{
    sfCircleShape *circle = sfCircleShape_create();

    if (!circle)
        return NULL;
    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setOrigin(circle, (sfVector2f){radius, radius});
    sfCircleShape_setPosition(circle, *pos);
    sfCircleShape_setFillColor(circle, *icolor);
    sfCircleShape_setOutlineThickness(circle, 8);
    sfCircleShape_setOutlineColor(circle, *ocolor);
    return circle;
}
