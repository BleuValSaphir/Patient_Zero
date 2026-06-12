/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** create_window
*/

#include "wolf.h"

sfRenderWindow *create_window(bool is_fullscreen)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window;
    sfUint32 style = is_fullscreen ? sfFullscreen : (sfTitlebar | sfClose);

    window = sfRenderWindow_create(mode, "Wolf3D", style, NULL);
    return window;
}
