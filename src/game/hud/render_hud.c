/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** render_hud.c
*/

#include "wolf.h"
#include <math.h>
#include <SFML/Graphics.h>

static void set_hud(global_t *glb)
{
    glb->hud->start_angle = 270.0f;
    glb->hud->total_angle = 180.0f;
    glb->hud->angle_step = glb->hud->total_angle / glb->hud->max_ammo;
    glb->hud->center = (sfVector2f){1700.0f, 850.0f};
    glb->hud->radius = 70.0f;
    glb->hud->current_ammo = WPN_AMMUNATION;
}

static void draw_ring(global_t *glb, sfRenderWindow *window,
    sfRectangleShape *bar)
{
    set_hud(glb);
    for (int i = 0; i < glb->hud->max_ammo; i++) {
        glb->hud->angle_deg = glb->hud->start_angle +
            (i * glb->hud->angle_step);
        glb->hud->angle_rad = glb->hud->angle_deg * (PI / 180.0f);
        glb->hud->x = glb->hud->center.x + cos(glb->hud->angle_rad)
            * glb->hud->radius;
        glb->hud->y = glb->hud->center.y + sin(glb->hud->angle_rad)
            * glb->hud->radius;
        sfRectangleShape_setPosition(bar,
            (sfVector2f){glb->hud->x, glb->hud->y});
        sfRectangleShape_setRotation(bar, glb->hud->angle_deg + 90.0f);
        if (i < glb->hud->current_ammo)
            sfRectangleShape_setFillColor(bar, sfWhite);
        else
            sfRectangleShape_setFillColor(bar, (sfColor){255, 255, 255, 100});
        sfRenderWindow_drawRectangleShape(window, bar, NULL);
    }
}

void render_ammo_bars(sfRenderWindow *window, global_t *glb)
{
    sfRectangleShape *bar = sfRectangleShape_create();
    sfVector2f bar_size = {6.0f, 18.0f};

    if (!bar)
        return;
    glb->hud->max_ammo = CUR_WEAPON.max_ammunation;
    if (glb->hud->max_ammo <= 0) {
        sfRectangleShape_destroy(bar);
        return;
    }
    sfRectangleShape_setSize(bar, bar_size);
    sfRectangleShape_setOrigin(bar, (sfVector2f)
        {bar_size.x / 2.0f, bar_size.y / 2.0f});
    draw_ring(glb, window, bar);
    sfRectangleShape_destroy(bar);
}

void draw_ammo_hud(global_t *glb, sfRenderWindow *window)
{
    if (glb->hud->munition && glb->hud->munition->sprite)
        sfRenderWindow_drawSprite(window, glb->hud->munition->sprite, NULL);
    if (TYPE == GUN && glb->hud->pistol_sprite &&
        glb->hud->pistol_sprite->sprite)
        sfRenderWindow_drawSprite(window,
            glb->hud->pistol_sprite->sprite, NULL);
    if (TYPE == MP5 && glb->hud->mp5_sprite && glb->hud->mp5_sprite->sprite)
        sfRenderWindow_drawSprite(window, glb->hud->mp5_sprite->sprite, NULL);
}

static void draw_ammo_txt(global_t *glb, sfRenderWindow *window)
{
    char ammo_str[20];
    char inv_str[20];

    sprintf(ammo_str, "%d", WPN_AMMUNATION);
    sprintf(inv_str, "%d", INV_AMMUNATION);
    if (glb->hud->ammo_text && glb->hud->ammo_text->text) {
        sfText_setString(glb->hud->ammo_text->text, ammo_str);
        sfRenderWindow_drawText(window, glb->hud->ammo_text->text, NULL);
    }
    if (glb->hud->inv_text && glb->hud->inv_text->text) {
        sfText_setString(glb->hud->inv_text->text, inv_str);
        sfRenderWindow_drawText(window, glb->hud->inv_text->text, NULL);
    }
}

static sfTexture *get_icon_tex(global_t *glb, int i, sfVector2u *sz,
    sfSprite *icon)
{
    sfTexture *tex = glb->hud->hotbar_icons[i];

    if (!tex)
        return NULL;
    sfSprite_setTexture(icon, tex, sfTrue);
    *sz = sfTexture_getSize(tex);
    return tex;
}

static void draw_weapon_icon(sfRenderWindow *window, global_t *glb,
    int i, sfVector2f *pos)
{
    sfSprite *icon = sfSprite_create();
    sfVector2u size;
    float scale;

    if (!get_icon_tex(glb, i, &size, icon)) {
        sfSprite_destroy(icon);
        return;
    }
    scale = 75.0f / (size.x > size.y ? size.x : size.y);
    sfSprite_setScale(icon, (sfVector2f){scale, scale});
    sfSprite_setOrigin(icon, (sfVector2f){size.x / 2.0f, size.y / 2.0f});
    sfSprite_setPosition(icon, (sfVector2f){pos->x + 45.0f, pos->y + 45.0f});
    sfRenderWindow_drawSprite(window, icon, NULL);
    sfSprite_destroy(icon);
}

static void setup_hotbar_rect(sfRectangleShape *rect)
{
    sfVector2f size = {90.0f, 90.0f};

    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setOutlineThickness(rect, 2.0f);
    sfRectangleShape_setOutlineColor(rect, (sfColor){255, 255, 255, 100});
}

static void render_inventory_hotbar(sfRenderWindow *window, global_t *glb)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2f pos;

    if (!rect)
        return;
    setup_hotbar_rect(rect);
    for (int i = 0; i < 5; i++) {
        pos = (sfVector2f){1270.0f + (i * 100.0f), 960.0f};
        sfRectangleShape_setPosition(rect, pos);
        sfRectangleShape_setFillColor(rect,
            (i == glb->game->inventory->cur_index) ?
            (sfColor){255, 255, 255, 150} : (sfColor){255, 255, 255, 50});
        sfRenderWindow_drawRectangleShape(window, rect, NULL);
        if (glb->game->inventory->indexes[i] == i)
            draw_weapon_icon(window, glb, i, &pos);
    }
    sfRectangleShape_destroy(rect);
}

void render_hud(sfRenderWindow *window, global_t *glb)
{
    if (!glb->hud || !glb->hud->is_visible)
        return;
    if (glb->hud->health_bg)
        sfRenderWindow_drawRectangleShape(window, glb->hud->health_bg, NULL);
    if (glb->hud->health_bar)
        sfRenderWindow_drawRectangleShape(window, glb->hud->health_bar, NULL);
    if (TYPE != KNIFE && TYPE != SPECIAL && TYPE != MEDKIT) {
        render_ammo_bars(window, glb);
        draw_ammo_hud(glb, window);
        draw_ammo_txt(glb, window);
    }
    render_inventory_hotbar(window, glb);
}
