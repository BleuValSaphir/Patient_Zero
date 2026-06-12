/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** minimap
*/
#include "wolf.h"

static void draw_minimap_cell(global_t *glb, int mx, int my,
    sfRectangleShape *wall)
{
    float dx = (float)mx - glb->player.x;
    float dy = (float)my - glb->player.y;
    sfVector2f pos = {1700.0f + (dx + M_RAD) * M_SIZE,
        60.0f + (dy + M_RAD) * M_SIZE};

    if (dx * dx + dy * dy > M_RAD * M_RAD)
        return;
    if (mx < 0 || mx >= MAP_WIDTH || my < 0 || my >= MAP_HEIGHT)
        return;
    if (glb->map[my][mx] == 1 || glb->map[my][mx] == 3) {
        sfRectangleShape_setFillColor(wall,
            sfColor_fromRGBA(200, 200, 200, 180));
        sfRectangleShape_setPosition(wall, pos);
        sfRenderWindow_drawRectangleShape(glb->window, wall, NULL);
    }
}

static void draw_player_fov(global_t *glb)
{
    sfConvexShape *fov = sfConvexShape_create();
    sfVector2f center = {1700.0f + M_RAD * M_SIZE, 60.0f + M_RAD * M_SIZE};
    float angle = glb->player.angle;
    float dist = 25.0f;

    sfConvexShape_setPointCount(fov, 3);
    sfConvexShape_setPoint(fov, 0, center);
    sfConvexShape_setPoint(fov, 1, (sfVector2f){
            center.x + cos(angle - FOV / 2) * dist,
            center.y + sin(angle - FOV / 2) * dist
    });
    sfConvexShape_setPoint(fov, 2, (sfVector2f){
            center.x + cos(angle + FOV / 2) * dist,
            center.y + sin(angle + FOV / 2) * dist
    });
    sfConvexShape_setFillColor(fov, sfColor_fromRGBA(255, 255, 255, 100));
    sfRenderWindow_drawConvexShape(glb->window, fov, NULL);
    sfConvexShape_destroy(fov);
}

static void draw_end_indicator(global_t *glb)
{
    sfCircleShape *indicator;
    float end_x = MAP_WIDTH - 1.5f;
    float end_y = MAP_HEIGHT - 1.5f;
    float dx = end_x - glb->player.x;
    float dy = end_y - glb->player.y;
    float angle;

    if (dx * dx + dy * dy > M_RAD * M_RAD) {
        indicator = sfCircleShape_create();
        angle = atan2(dy, dx);
        sfCircleShape_setRadius(indicator, 4.0f);
        sfCircleShape_setOrigin(indicator, (sfVector2f){4.0f, 4.0f});
        sfCircleShape_setPosition(indicator, (sfVector2f){
                1700.0f + M_RAD * M_SIZE + cos(angle) * (M_RAD * M_SIZE - 4.0f),
                60.0f + M_RAD * M_SIZE + sin(angle) * (M_RAD * M_SIZE - 4.0f)});
        sfCircleShape_setFillColor(indicator, sfGreen);
        sfRenderWindow_drawCircleShape(glb->window, indicator, NULL);
        sfCircleShape_destroy(indicator);
    }
}

static void setup_and_draw_minimap(global_t *glb, sfCircleShape *bg,
    sfRectangleShape *wall, sfCircleShape *player)
{
    int p_x = (int)glb->player.x;
    int p_y = (int)glb->player.y;

    sfCircleShape_setRadius(bg, M_RAD * M_SIZE);
    sfCircleShape_setPosition(bg, (sfVector2f){1700.0f, 60.0f});
    sfCircleShape_setFillColor(bg, sfColor_fromRGBA(0, 0, 0, 150));
    sfRenderWindow_drawCircleShape(glb->window, bg, NULL);
    sfRectangleShape_setSize(wall, (sfVector2f){M_SIZE, M_SIZE});
    sfRectangleShape_setFillColor(wall, sfColor_fromRGBA(200, 200, 200, 180));
    for (int y = p_y - M_RAD - 1; y <= p_y + M_RAD + 1; y++) {
        for (int x = p_x - M_RAD - 1; x <= p_x + M_RAD + 1; x++)
            draw_minimap_cell(glb, x, y, wall);
    }
    draw_player_fov(glb);
    draw_end_indicator(glb);
    sfCircleShape_setRadius(player, 3.0f);
    sfCircleShape_setPosition(player, (sfVector2f){1700.0f + M_RAD *
            M_SIZE - 3.0f, 60.0f + M_RAD * M_SIZE - 3.0f});
    sfCircleShape_setFillColor(player, sfRed);
    sfRenderWindow_drawCircleShape(glb->window, player, NULL);
}

void render_minimap(global_t *glb)
{
    if (!glb || !glb->map)
        return;
    setup_and_draw_minimap(glb, glb->game->minimap->bg,
        glb->game->minimap->wall, glb->game->minimap->player);
}
