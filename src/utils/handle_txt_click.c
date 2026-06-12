/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** handle_txt_click.c
*/

#include "utils.h"

bool is_text_clicked(text_t *txt, sfEvent *event)
{
    float mouse_x = (float)event->mouseButton.x;
    float mouse_y = (float)event->mouseButton.y;
    sfFloatRect bounds;

    if (!txt || !txt->text)
        return false;
    bounds = sfText_getGlobalBounds(txt->text);
    if (event->type != sfEvtMouseButtonPressed ||
        event->mouseButton.button != sfMouseLeft)
        return false;
    if (sfFloatRect_contains(&bounds, mouse_x, mouse_y))
        return true;
    return false;
}
