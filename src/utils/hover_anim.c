/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** hover_anim.c
*/

#include "wolf.h"

void handle_hover_anim(sfRenderWindow *window, text_t *txt)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfVector2f mouse_float = sfRenderWindow_mapPixelToCoords(window,
        mouse_pos, NULL);
    sfFloatRect bounds;
    sfVector2f hover_scale = {1.2f, 1.2f};
    sfVector2f scale = {1.0f, 1.0f};

    if (!txt || !txt->text)
        return;
    bounds = sfText_getGlobalBounds(txt->text);
    if (sfFloatRect_contains(&bounds, mouse_float.x, mouse_float.y))
        sfText_setScale(txt->text, hover_scale);
    else
        sfText_setScale(txt->text, scale);
}

void handle_color_anim(sfRenderWindow *window, text_t *txt)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfVector2f mouse_float = sfRenderWindow_mapPixelToCoords(window,
        mouse_pos, NULL);
    sfFloatRect bounds;

    if (!txt || !txt->text)
        return;
    bounds = sfText_getGlobalBounds(txt->text);
    if (sfFloatRect_contains(&bounds, mouse_float.x, mouse_float.y))
        sfText_setColor(txt->text, sfWhite);
    else
        sfText_setColor(txt->text, (sfColor){128, 128, 128, 255});
}
