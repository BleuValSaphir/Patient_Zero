/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** game_over
*/

#include "game.h"

void render_game_over(sfRenderWindow *window, global_t *glb)
{
    sfRectangleShape *bg = sfRectangleShape_create();

    sfRectangleShape_setSize(bg, (sfVector2f){1920.f, 1080.f});
    sfRectangleShape_setFillColor(bg,
        (sfColor){0, 0, 0, (sfUint8)glb->game->game_over_fade});
    sfRenderWindow_drawRectangleShape(window, bg, NULL);
    sfRectangleShape_destroy(bg);
    if (glb->game->game_over_fade >= 255.0f) {
        sfRenderWindow_setMouseCursorVisible(window, sfTrue);
        sfRenderWindow_drawText(window, glb->game->game_over_title->text, NULL);
        sfRenderWindow_drawText(window, glb->game->game_over_restart->text,
            NULL);
        sfRenderWindow_drawText(window, glb->game->game_over_menu->text,
            NULL);
    }
}

void handle_game_over_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene)
{
    if (glb->game->game_over_fade < 255.0f)
        return;
    if (is_text_clicked(glb->game->game_over_restart, event) &&
        event->type == sfEvtMouseButtonPressed) {
        destroy_game(glb);
        init_game(glb);
    } else if (is_text_clicked(glb->game->game_over_menu, event) &&
        event->type == sfEvtMouseButtonPressed)
        *next_scene = SCENE_MAIN_MENU;
}
