/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** player.c
*/

#include "wolf.h"

static void manage_pitch(player_t *player)
{
    if (player->true_pitch > 700)
        player->true_pitch = 700;
    if (player->true_pitch < -700)
        player->true_pitch = -700;
}

static void update_joystick_camera(player_t *player, global_t *glb)
{
    float joy_u = 0;
    float joy_v = 0;
    float joy_z = 0;
    float joy_r = 0;

    if (sfJoystick_isConnected(0)) {
        joy_u = sfJoystick_getAxisPosition(0, sfJoystickU);
        joy_v = sfJoystick_getAxisPosition(0, sfJoystickV);
        joy_z = sfJoystick_getAxisPosition(0, sfJoystickZ);
        joy_r = sfJoystick_getAxisPosition(0, sfJoystickR);
    }
    if (fabs(joy_u) < 20.f)
        joy_u = joy_z;
    if (fabs(joy_v) < 20.f)
        joy_v = joy_r;
    if (fabs(joy_u) > 20.f)
        player->angle += joy_u * 0.0004f * glb->mouse_sens;
    if (fabs(joy_v) > 20.f)
        player->true_pitch -= joy_v * 0.5f;
}

void update_mouse(player_t *player, sfRenderWindow *window, global_t *glb)
{
    sfVector2i center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);
    int dx = pos.x - center.x;
    int dy = pos.y - center.y;

    player->smooth_dx += (dx - player->smooth_dx) * 0.5f;
    player->smooth_dy += (dy - player->smooth_dy) * 0.5f;
    player->angle += player->smooth_dx * 0.003f * glb->mouse_sens;
    update_joystick_camera(player, glb);
    if (player->angle < 0)
        player->angle += 2 * PI;
    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    player->true_pitch -= player->smooth_dy * 1.5f;
    manage_pitch(player);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    sfMouse_setPositionRenderWindow(center, window);
}

static void get_direction_inputs(global_t *glb, bool *dirs)
{
    float joy_x = 0;
    float joy_y = 0;

    if (sfJoystick_isConnected(0)) {
        joy_x = sfJoystick_getAxisPosition(0, sfJoystickX);
        joy_y = sfJoystick_getAxisPosition(0, sfJoystickY);
    }
    dirs[0] = sfKeyboard_isKeyPressed(glb->is_qwerty ? sfKeyW : sfKeyZ) ||
        joy_y < -20.f;
    dirs[1] = sfKeyboard_isKeyPressed(sfKeyS) || joy_y > 20.f;
    dirs[2] = sfKeyboard_isKeyPressed(glb->is_qwerty ? sfKeyA : sfKeyQ) ||
        joy_x < -20.f;
    dirs[3] = sfKeyboard_isKeyPressed(sfKeyD) || joy_x > 20.f;
}

static void apply_direction(global_t *glb, float *moveX, float *moveY,
    float actual_speed, bool *dirs)
{
    if (dirs[0]) {
        *moveX += cos(glb->player.angle) * actual_speed;
        *moveY += sin(glb->player.angle) * actual_speed;
    }
    if (dirs[1]) {
        *moveX -= cos(glb->player.angle) * actual_speed;
        *moveY -= sin(glb->player.angle) * actual_speed;
    }
    if (dirs[2]) {
        *moveX += cos(glb->player.angle - PI / 2) * actual_speed / 2;
        *moveY += sin(glb->player.angle - PI / 2) * actual_speed / 2;
    }
    if (dirs[3]) {
        *moveX += cos(glb->player.angle + PI / 2) * actual_speed / 2;
        *moveY += sin(glb->player.angle + PI / 2) * actual_speed / 2;
    }
}

void manage_direction(global_t *glb, float speed, float *moveX, float *moveY)
{
    float actual_speed = speed * glb->game->weapon[TYPE].mass_factor;
    bool dirs[4] = {false};
    bool is_sprinting = sfKeyboard_isKeyPressed(sfKeyLShift) ||
        (sfJoystick_isConnected(0) && sfJoystick_isButtonPressed(0, 8));

    get_direction_inputs(glb, dirs);
    if (is_sprinting && dirs[0])
        actual_speed *= 1.6f;
    apply_direction(glb, moveX, moveY, actual_speed, dirs);
}

void update_mouv(player_t *player, global_t *glb, float moveX, float moveY)
{
    float padX;
    float padY;

    if (moveX != 0.0f) {
        padX = (moveX > 0) ? 0.2f : -0.2f;
        if (!is_wall(glb, (int)(player->x + moveX + padX), (int)player->y,
                glb->map))
            player->x += moveX;
    }
    if (moveY != 0.0f) {
        padY = (moveY > 0) ? 0.2f : -0.2f;
        if (!is_wall(glb, (int)player->x, (int)(player->y + moveY + padY),
                glb->map))
            player->y += moveY;
    }
    sfClock_restart(player->movement_clock);
}

static void update_headbobbing(player_t *player, float seconds, float moveX,
    float moveY)
{
    if (moveX != 0.0f || moveY != 0.0f) {
        player->bob_time += seconds * 12.0f;
        if (player->bob_time > PI * 2)
            player->bob_time -= PI * 2;
    }
    if (moveX == 0.0f && moveY == 0.0f && player->bob_time > 0.0f) {
        player->bob_time += seconds * 12.0f;
        if (player->bob_time > PI * 2)
            player->bob_time = 0.0f;
    }
    player->pitch = (int)(player->true_pitch +
        sin(player->bob_time) * 12.0f);
}

void update_player(global_t *glb)
{
    player_t *player = &glb->player;
    float moveX = 0;
    float moveY = 0;
    float seconds = sfTime_asSeconds(
        sfClock_getElapsedTime(player->movement_clock));

    if (seconds >= 0.01f) {
        manage_direction(glb, SPEED * seconds * 60.0f, &moveX, &moveY);
        update_mouv(player, glb, moveX, moveY);
        if (glb->headbobbing)
            update_headbobbing(player, seconds, moveX, moveY);
        else
            player->pitch = (int)player->true_pitch;
    }
    if (player->health <= 0)
        player->health = 0;
}

void init_player(player_t *player)
{
    player->x = 1.5f;
    player->y = 1.5f;
    player->angle = PI / 2;
    player->health_max = 100;
    player->health = 100;
    player->pitch = 0;
    player->movement_clock = sfClock_create();
    player->smooth_dx = 0.0f;
    player->smooth_dy = 0.0f;
    player->true_pitch = 0.0f;
    player->bob_time = 0.0f;
}
