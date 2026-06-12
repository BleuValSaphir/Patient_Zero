/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** resize_window.c
*/

#include "wolf.h"

static void set_window_view(global_t *glb)
{
    sfView *view = sfView_createFromRect((sfFloatRect){0, 0, SCREEN_WIDTH,
            SCREEN_HEIGHT});

    if (view) {
        sfRenderWindow_setView(glb->window, view);
        sfView_destroy(view);
    }
}

void resize_window(global_t *glb, unsigned int width, unsigned int height,
    bool is_fullscreen)
{
    sfVideoMode mode = {width, height, 32};
    sfUint32 style = is_fullscreen ? sfFullscreen : sfClose;
    sfRenderWindow *new_win;

    new_win = sfRenderWindow_create(mode, "Wolf3D", style, NULL);
    if (!new_win)
        return;
    if (glb->window)
        sfRenderWindow_destroy(glb->window);
    glb->window = new_win;
    sfRenderWindow_setFramerateLimit(glb->window, 120);
    if (!is_fullscreen)
        sfRenderWindow_setPosition(glb->window, (sfVector2i){
                (1920 - width) / 2, (1080 - height) / 2});
    set_window_view(glb);
}

void resize_cond(global_t *glb, bool resize)
{
    if (resize)
        resize_window(glb, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    else
        resize_window(glb, SCREEN_WIDTH, SCREEN_HEIGHT, true);
    sfListener_setGlobalVolume(glb->volume);
}
