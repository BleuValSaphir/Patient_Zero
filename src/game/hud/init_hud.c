/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** init_hud.c
*/

#include "wolf.h"

static void init_health_bar(global_t *glb)
{
    glb->hud->health_bg = sfRectangleShape_create();
    sfRectangleShape_setSize(glb->hud->health_bg,
        (sfVector2f){150.0f, 6.0f});
    sfRectangleShape_setFillColor(glb->hud->health_bg,
        sfColor_fromRGBA(255, 255, 255, 50));
    sfRectangleShape_setPosition(glb->hud->health_bg,
        (sfVector2f){50.0f, 950.0f});
    glb->hud->health_bar = sfRectangleShape_create();
    sfRectangleShape_setSize(glb->hud->health_bar,
        (sfVector2f){150.0f, 10.0f});
    sfRectangleShape_setFillColor(glb->hud->health_bar, sfWhite);
    sfRectangleShape_setPosition(glb->hud->health_bar,
        (sfVector2f){50.0f, 950.0f});
}

static void init_hud_values(global_t *glb)
{
    glb->hud->display_timer = 0.0f;
    glb->hud->is_visible = false;
    glb->hud->last_health = glb->player.health;
    glb->hud->last_weapon_index = glb->game->inventory->cur_index;
    glb->hud->hotbar_icons[0] = sfTexture_createFromFile(
        "assets/sprites/knife.png", NULL);
    glb->hud->hotbar_icons[1] = sfTexture_createFromFile(
        "assets/sprites/Pistol.png", NULL);
    glb->hud->hotbar_icons[2] = sfTexture_createFromFile(
        "assets/sprites/MP5.png", NULL);
    glb->hud->hotbar_icons[3] = sfTexture_createFromFile(
        "assets/sprites/hand.png", NULL);
    glb->hud->hotbar_icons[4] = sfTexture_createFromFile(
        "assets/sprites/syringe.png", NULL);
}

void init_hud(global_t *glb)
{
    glb->hud = malloc(sizeof(hud_t));
    if (!glb->hud)
        return;
    memset(glb->hud, 0, sizeof(hud_t));
    init_health_bar(glb);
    glb->hud->ammo_text = set_text(&sfWhite, &(sfVector2f){1700.0f, 860.0f},
        &(text_info_t){"assets/font/Roboto.ttf", "0", 26});
    glb->hud->inv_text = set_text(&sfWhite, &(sfVector2f){1650.0f, 900.0f},
        &(text_info_t){"assets/font/Roboto.ttf", "0", 26});
    glb->hud->munition = set_sprite("assets/sprites/balles.png",
        &(sfVector2f){0.5f, 0.5f},
        &(sfVector2f){0.0f, 0.0f}, &(sfVector2f){1600.0f, 895.0f});
    glb->hud->pistol_sprite = set_sprite("assets/sprites/Pistol.png",
        &(sfVector2f){0.2f, 0.2f},
        &(sfVector2f){0.0f, 0.0f}, &(sfVector2f){1570.0f, 795.0f});
    glb->hud->mp5_sprite = set_sprite("assets/sprites/MP5.png",
        &(sfVector2f){0.2f, 0.2f},
        &(sfVector2f){0.0f, 0.0f}, &(sfVector2f){1500.0f, 795.0f});
    init_hud_values(glb);
}
