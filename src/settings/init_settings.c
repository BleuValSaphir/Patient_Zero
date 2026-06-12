/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** init_settings.c
*/

#include "wolf.h"


void init_sound(global_t *glb)
{
    char vol_str[10];

    glb->audio_txt = set_text(&sfWhite,
        &(sfVector2f){50.f, 150.f}, &(text_info_t){"assets/font/Roboto.ttf",
            "Audio", 30});
    glb->arrow_left = set_text(&sfWhite,
        &(sfVector2f){500.f, 150.f}, &(text_info_t){"assets/font/Roboto.ttf",
            "<", 30});
    glb->arrow_right = set_text(&sfWhite,
        &(sfVector2f){610.f, 150.f}, &(text_info_t){"assets/font/Roboto.ttf",
            ">", 30});
    sprintf(vol_str, "%d", glb->volume);
    glb->vol_display = set_text(&sfWhite,
        &(sfVector2f){550.f, 150.f}, &(text_info_t){"assets/font/Roboto.ttf",
            vol_str, 30});
}

static void init_comfort_layout(global_t *glb)
{
    glb->headbobbing_txt = set_text(&sfWhite, &(sfVector2f){50.f, 290.f},
        &(text_info_t){"assets/font/Roboto.ttf", "Headbobbing", 30});
    glb->headbobbing_toggle = set_text(&sfWhite, &(sfVector2f){550.f, 290.f},
        &(text_info_t){"assets/font/Roboto.ttf",
            glb->headbobbing ? "ON" : "OFF", 30});
    glb->layout_txt = set_text(&sfWhite, &(sfVector2f){50.f, 360.f},
        &(text_info_t){"assets/font/Roboto.ttf", "Keyboard Layout", 30});
    glb->layout_toggle = set_text(&sfWhite, &(sfVector2f){550.f, 360.f},
        &(text_info_t){"assets/font/Roboto.ttf",
            glb->is_qwerty ? "QWERTY" : "AZERTY", 30});
}

static void init_comfort(global_t *glb)
{
    char sens[10];

    sprintf(sens, "%.1f", glb->mouse_sens);
    glb->sens_txt = set_text(&sfWhite, &(sfVector2f){50.f, 220.f},
        &(text_info_t){"assets/font/Roboto.ttf", "Mouse Sensibility", 30});
    glb->sens_left = set_text(&sfWhite, &(sfVector2f){500.f, 220.f},
        &(text_info_t){"assets/font/Roboto.ttf", "<", 30});
    glb->sens_right = set_text(&sfWhite, &(sfVector2f){610.f, 220.f},
        &(text_info_t){"assets/font/Roboto.ttf", ">", 30});
    glb->sens_display = set_text(&sfWhite, &(sfVector2f){550.f, 220.f},
        &(text_info_t){"assets/font/Roboto.ttf", sens, 30});
    init_comfort_layout(glb);
}

static void init_fps(global_t *glb)
{
    char fps_str[10];

    if (glb->fps_limit == 0)
        strcpy(fps_str, "MAX");
    else
        sprintf(fps_str, "%d", glb->fps_limit);
    glb->fps_txt = set_text(&sfWhite, &(sfVector2f){50.f, 430.f},
        &(text_info_t){"assets/font/Roboto.ttf", "FPS Limit", 30});
    glb->fps_left = set_text(&sfWhite, &(sfVector2f){500.f, 430.f},
        &(text_info_t){"assets/font/Roboto.ttf", "<", 30});
    glb->fps_right = set_text(&sfWhite, &(sfVector2f){610.f, 430.f},
        &(text_info_t){"assets/font/Roboto.ttf", ">", 30});
    glb->fps_display = set_text(&sfWhite, &(sfVector2f){550.f, 430.f},
        &(text_info_t){"assets/font/Roboto.ttf", fps_str, 30});
}

void init_button(global_t *glb)
{
    if (!glb)
        return;
    glb->full_screen_txt = set_text(&sfWhite,
        &(sfVector2f){50.f, 80.f}, &(text_info_t){"assets/font/Roboto.ttf",
            "Full Screen", 30});
    glb->toggle_txt = set_text(&sfWhite,
        &(sfVector2f){550.f, 80.f}, &(text_info_t){"assets/font/Roboto.ttf",
            "ON", 30});
    if (glb->is_fullscreen)
        sfText_setString(glb->toggle_txt->text, "ON");
    else
        sfText_setString(glb->toggle_txt->text, "OFF");
    init_sound(glb);
    init_comfort(glb);
    init_fps(glb);
}

void init_settings_texts(global_t *glb)
{
    if (!glb)
        return;
    glb->settings_txt = set_text(&sfWhite,
        &(sfVector2f){30.f, 10.f}, &(text_info_t){
            "assets/font/Roboto.ttf", "OPTIONS", 40});
    glb->exit_txt = set_text(&sfWhite,
        &(sfVector2f){1810.f, 10.f}, &(text_info_t){"assets/font/Roboto.ttf",
            "Exit", 30});
    init_button(glb);
}

void init_settings(global_t *glb)
{
    sfVector2u tex_size;
    sfVector2f scale;

    if (!glb)
        return;
    glb->texture = sfTexture_createFromFile("assets/sprites/settings.jpg",
        NULL);
    glb->sprite = sfSprite_create();
    if (glb->texture && glb->sprite) {
        tex_size = sfTexture_getSize(glb->texture);
        sfSprite_setTexture(glb->sprite, glb->texture, sfTrue);
        scale.x = 1920.f / tex_size.x;
        scale.y = 1080.f / tex_size.y;
        sfSprite_setScale(glb->sprite, scale);
    }
    init_settings_texts(glb);
}
