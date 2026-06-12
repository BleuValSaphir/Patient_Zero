/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** handle_settings_event.c
*/

#include "wolf.h"

static void display_volume(global_t *glb, bool volume_changed)
{
    char vol_str[10];

    if (volume_changed) {
        sprintf(vol_str, "%d", glb->volume);
        sfText_setString(glb->vol_display->text, vol_str);
        sfListener_setGlobalVolume(glb->volume);
        if (glb->menu_sound)
            sfSound_play(glb->menu_sound->sound);
    }
}

void handle_volume(global_t *glb, sfEvent *event)
{
    bool volume_changed = false;

    if (!glb || !event)
        return;
    if (glb->arrow_left && is_text_clicked(glb->arrow_left, event)) {
        glb->volume -= 5;
        if (glb->volume < 0)
            glb->volume = 0;
        volume_changed = true;
    }
    if (glb->arrow_right && is_text_clicked(glb->arrow_right, event)) {
        glb->volume += 5;
        if (glb->volume > 100)
            glb->volume = 100;
        volume_changed = true;
    }
    display_volume(glb, volume_changed);
}

static void display_sens(global_t *glb, bool sens_changed)
{
    char sens_str[10];

    if (sens_changed && glb->sens_display) {
        sprintf(sens_str, "%.1f", glb->mouse_sens);
        sfText_setString(glb->sens_display->text, sens_str);
        if (glb->menu_sound)
            sfSound_play(glb->menu_sound->sound);
    }
}

static void handle_comfort_sens(global_t *glb, sfEvent *event)
{
    bool sens_changed = false;

    if (glb->sens_left && is_text_clicked(glb->sens_left, event)) {
        glb->mouse_sens = (glb->mouse_sens <= 0.1f) ?
            0.1f : glb->mouse_sens - 0.1f;
        sens_changed = true;
    }
    if (glb->sens_right && is_text_clicked(glb->sens_right, event)) {
        glb->mouse_sens = (glb->mouse_sens >= 3.0f) ?
            3.0f : glb->mouse_sens + 0.1f;
        sens_changed = true;
    }
    display_sens(glb, sens_changed);
}

static void handle_comfort_toggles(global_t *glb, sfEvent *event)
{
    if (glb->headbobbing_toggle && is_text_clicked(
            glb->headbobbing_toggle, event) &&
        event->type == sfEvtMouseButtonPressed) {
        glb->headbobbing = !glb->headbobbing;
        sfText_setString(glb->headbobbing_toggle->text,
            glb->headbobbing ? "ON" : "OFF");
    }
    if (glb->layout_toggle && is_text_clicked(glb->layout_toggle, event) &&
        event->type == sfEvtMouseButtonPressed) {
        glb->is_qwerty = !glb->is_qwerty;
        sfText_setString(glb->layout_toggle->text,
            glb->is_qwerty ? "QWERTY" : "AZERTY");
    }
}

static void display_fps(global_t *glb, bool fps_changed)
{
    char fps_str[10];

    if (fps_changed && glb->fps_display) {
        if (glb->fps_limit == 0)
            strcpy(fps_str, "MAX");
        else
            sprintf(fps_str, "%d", glb->fps_limit);
        sfText_setString(glb->fps_display->text, fps_str);
        sfRenderWindow_setFramerateLimit(glb->window, glb->fps_limit);
        if (glb->menu_sound)
            sfSound_play(glb->menu_sound->sound);
    }
}

static void get_next_fps(global_t *glb, int dir)
{
    int fps_values[] = {30, 60, 90, 120, 144, 200, 0};
    int num_values = 7;
    int i = 0;

    for (; i < num_values; i++) {
        if (glb->fps_limit == fps_values[i])
            break;
    }
    if (i == num_values)
        i = 3;
    i += dir;
    if (i < 0)
        i = num_values - 1;
    if (i >= num_values)
        i = 0;
    glb->fps_limit = fps_values[i];
}

static void handle_fps_limit(global_t *glb, sfEvent *event)
{
    bool fps_changed = false;

    if (glb->fps_left && is_text_clicked(glb->fps_left, event)) {
        get_next_fps(glb, -1);
        fps_changed = true;
    }
    if (glb->fps_right && is_text_clicked(glb->fps_right, event)) {
        get_next_fps(glb, 1);
        fps_changed = true;
    }
    display_fps(glb, fps_changed);
}

static void handle_fullscreen_toggle(global_t *glb, sfEvent *event)
{
    if (glb->toggle_txt && is_text_clicked(glb->toggle_txt, event) &&
        event->type == sfEvtMouseButtonPressed) {
        glb->is_fullscreen = !glb->is_fullscreen;
        if (glb->is_fullscreen) {
            sfText_setString(glb->toggle_txt->text, "ON");
            resize_cond(glb, false);
        } else {
            sfText_setString(glb->toggle_txt->text, "OFF");
            resize_cond(glb, true);
        }
    }
}

void handle_settings_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene)
{
    if (!glb || !event || !next_scene)
        return;
    if (glb->exit_txt && is_text_clicked(glb->exit_txt, event) &&
        event->type == sfEvtMouseButtonPressed) {
        save_settings(glb);
        *next_scene = SCENE_MAIN_MENU;
    }
    handle_fullscreen_toggle(glb, event);
    handle_volume(glb, event);
    handle_comfort_sens(glb, event);
    handle_comfort_toggles(glb, event);
    handle_fps_limit(glb, event);
}
