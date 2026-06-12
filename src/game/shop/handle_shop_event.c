/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** handle_shop_event
*/

#include "game.h"

bool is_schema_clicked(sfRectangleShape *rect, sfEvent *event)
{
    float mouse_x = (float)event->mouseButton.x;
    float mouse_y = (float)event->mouseButton.y;
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(rect);

    if (event->type != sfEvtMouseButtonPressed ||
        event->mouseButton.button != sfMouseLeft)
        return false;
    if (sfFloatRect_contains(&bounds, mouse_x, mouse_y))
        return true;
    return false;
}

void handle_shop_event(global_t *glb, sfEvent *event)
{
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyB) {
        glb->game->shop.in_shop = true;
        sfRenderWindow_setMouseCursorVisible(glb->window, sfTrue);
    }
    if (event->type == sfEvtKeyReleased && event->key.code == sfKeyB) {
        glb->game->shop.in_shop = false;
        sfMouse_setPositionRenderWindow((sfVector2i){SCREEN_WIDTH / 2,
                SCREEN_HEIGHT / 2}, glb->window);
    }
    if (!SHOP.in_shop)
        return;
    for (int index = 0; index < NB_ARMORY_EMPLACEMENT; index++) {
        if (is_schema_clicked(SHOP.articles[index], event))
            get_item[index](glb);
    }
}
