/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** main_menu_init.c
*/

#include "wolf.h"

static void init_main_menu_texts(global_t *glb)
{
    sfVector2f pos = {1500.f, 300.f};
    sfVector2f pos_load = {1670.f, 500.f};
    sfVector2f pos_settings = {1600.f, 400.f};
    sfVector2f pos_quit = {1700.f, 600.f};
    sfColor yellow = {255, 255, 0, 255};
    text_info_t info = {"assets/font/Branda-yolq.ttf", "New Game", 70};
    text_info_t info_load = {"assets/font/Branda-yolq.ttf", "Load", 70};
    text_info_t info_settings = {"assets/font/Branda-yolq.ttf", "Settings", 70};
    text_info_t info_quit = {"assets/font/Branda-yolq.ttf", "Quit", 70};

    glb->init_text = set_text(&yellow, &pos, &info);
    glb->load_txt = set_text(&yellow, &pos_load, &info_load);
    glb->settings_txt = set_text(&yellow, &pos_settings, &info_settings);
    glb->quit_txt = set_text(&yellow, &pos_quit, &info_quit);
}

void init_main_menu(global_t *glb)
{
    if (!glb)
        return;
    glb->texture = sfTexture_createFromFile("assets/sprites/"
        "main_menu.jpg", NULL);
    glb->sprite = sfSprite_create();
    if (glb->texture) {
        sfSprite_setTexture(glb->sprite, glb->texture, sfTrue);
    }
    sfRenderWindow_setMouseCursorVisible(glb->window, sfTrue);
    init_main_menu_texts(glb);
    glb->epilogue_sound = set_sound("assets/sounds/Epilogue.mp3", 100.0f);
}
