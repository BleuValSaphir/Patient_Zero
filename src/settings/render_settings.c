/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** render_settings.c
*/

#include "wolf.h"

static void render_base_settings(sfRenderWindow *window, global_t *glb)
{
    if (!window || !glb)
        return;
    if (glb->settings_txt)
        sfRenderWindow_drawText(window, glb->settings_txt->text, NULL);
    if (glb->full_screen_txt)
        sfRenderWindow_drawText(window, glb->full_screen_txt->text, NULL);
    if (glb->audio_txt)
        sfRenderWindow_drawText(window, glb->audio_txt->text, NULL);
    if (glb->toggle_txt)
        sfRenderWindow_drawText(window, glb->toggle_txt->text, NULL);
    if (glb->arrow_left)
        sfRenderWindow_drawText(window, glb->arrow_left->text, NULL);
    if (glb->arrow_right)
        sfRenderWindow_drawText(window, glb->arrow_right->text, NULL);
    if (glb->vol_display)
        sfRenderWindow_drawText(window, glb->vol_display->text, NULL);
    if (glb->exit_txt)
        sfRenderWindow_drawText(window, glb->exit_txt->text, NULL);
}

static void render_comfort(sfRenderWindow *window, global_t *glb)
{
    if (glb->sens_txt)
        sfRenderWindow_drawText(window, glb->sens_txt->text, NULL);
    if (glb->sens_left)
        sfRenderWindow_drawText(window, glb->sens_left->text, NULL);
    if (glb->sens_right)
        sfRenderWindow_drawText(window, glb->sens_right->text, NULL);
    if (glb->sens_display)
        sfRenderWindow_drawText(window, glb->sens_display->text, NULL);
    if (glb->headbobbing_txt)
        sfRenderWindow_drawText(window, glb->headbobbing_txt->text, NULL);
    if (glb->headbobbing_toggle)
        sfRenderWindow_drawText(window, glb->headbobbing_toggle->text, NULL);
    if (glb->layout_txt)
        sfRenderWindow_drawText(window, glb->layout_txt->text, NULL);
    if (glb->layout_toggle)
        sfRenderWindow_drawText(window, glb->layout_toggle->text, NULL);
}

static void render_fps(sfRenderWindow *window, global_t *glb)
{
    if (glb->fps_txt)
        sfRenderWindow_drawText(window, glb->fps_txt->text, NULL);
    if (glb->fps_left)
        sfRenderWindow_drawText(window, glb->fps_left->text, NULL);
    if (glb->fps_right)
        sfRenderWindow_drawText(window, glb->fps_right->text, NULL);
    if (glb->fps_display)
        sfRenderWindow_drawText(window, glb->fps_display->text, NULL);
}

void render_settings_texts(sfRenderWindow *window, global_t *glb)
{
    render_base_settings(window, glb);
    render_comfort(window, glb);
    render_fps(window, glb);
}

void render_settings(sfRenderWindow *window, global_t *glb)
{
    if (!window || !glb)
        return;
    if (glb->sprite)
        sfRenderWindow_drawSprite(window, glb->sprite, NULL);
    draw_generic_popup(window, &(sfColor){0, 0, 0, 200},
        &(sfVector2f){1920.f, 1080.f}, &(sfVector2f){1920.f, 1080.f});
    render_settings_texts(window, glb);
}
