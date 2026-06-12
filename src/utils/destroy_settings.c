/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** destroy_settings.c
*/

#include "wolf.h"

static void destroy_base_txt(global_t *glb)
{
    if (glb->settings_txt) {
        destroy_text(glb->settings_txt);
        glb->settings_txt = NULL;
    }
    if (glb->full_screen_txt) {
        destroy_text(glb->full_screen_txt);
        glb->full_screen_txt = NULL;
    }
    if (glb->audio_txt) {
        destroy_text(glb->audio_txt);
        glb->audio_txt = NULL;
    }
    if (glb->toggle_txt) {
        destroy_text(glb->toggle_txt);
        glb->toggle_txt = NULL;
    }
}

void destroy_txt(global_t *glb)
{
    destroy_base_txt(glb);
    if (glb->arrow_left) {
        destroy_text(glb->arrow_left);
        glb->arrow_left = NULL;
    }
    if (glb->arrow_right) {
        destroy_text(glb->arrow_right);
        glb->arrow_right = NULL;
    }
    if (glb->vol_display) {
        destroy_text(glb->vol_display);
        glb->vol_display = NULL;
    }
    if (glb->exit_txt) {
        destroy_text(glb->exit_txt);
        glb->exit_txt = NULL;
    }
}

static void destroy_comfort_sens_txt(global_t *glb)
{
    if (glb->sens_txt) {
        destroy_text(glb->sens_txt);
        glb->sens_txt = NULL;
    }
    if (glb->sens_left) {
        destroy_text(glb->sens_left);
        glb->sens_left = NULL;
    }
    if (glb->sens_right) {
        destroy_text(glb->sens_right);
        glb->sens_right = NULL;
    }
    if (glb->sens_display) {
        destroy_text(glb->sens_display);
        glb->sens_display = NULL;
    }
}

static void destroy_comfort_txt(global_t *glb)
{
    destroy_comfort_sens_txt(glb);
    if (glb->headbobbing_txt) {
        destroy_text(glb->headbobbing_txt);
        glb->headbobbing_txt = NULL;
    }
    if (glb->headbobbing_toggle) {
        destroy_text(glb->headbobbing_toggle);
        glb->headbobbing_toggle = NULL;
    }
    if (glb->layout_txt) {
        destroy_text(glb->layout_txt);
        glb->layout_txt = NULL;
    }
    if (glb->layout_toggle) {
        destroy_text(glb->layout_toggle);
        glb->layout_toggle = NULL;
    }
}

static void destroy_fps_txt(global_t *glb)
{
    if (glb->fps_txt) {
        destroy_text(glb->fps_txt);
        glb->fps_txt = NULL;
    }
    if (glb->fps_left) {
        destroy_text(glb->fps_left);
        glb->fps_left = NULL;
    }
    if (glb->fps_right) {
        destroy_text(glb->fps_right);
        glb->fps_right = NULL;
    }
    if (glb->fps_display) {
        destroy_text(glb->fps_display);
        glb->fps_display = NULL;
    }
}

void destroy_settings_texts(global_t *glb)
{
    destroy_txt(glb);
    destroy_comfort_txt(glb);
    destroy_fps_txt(glb);
}

void destroy_settings(global_t *glb)
{
    if (!glb)
        return;
    destroy_settings_texts(glb);
    if (glb->texture) {
        sfTexture_destroy(glb->texture);
        glb->texture = NULL;
    }
    if (glb->sprite) {
        sfSprite_destroy(glb->sprite);
        glb->sprite = NULL;
    }
}
