/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** handle_game_event.c
*/

#include "wolf.h"

static void handle_inventory_joystick(inventory_t *inv, sfEvent *event)
{
    bool no_medkit;

    if (event->type != sfEvtJoystickButtonPressed ||
        event->joystickButton.button != 4)
        return;
    inv->cur_index++;
    no_medkit = inv->indexes[MEDKIT] != MEDKIT ||
        inv->cur_ammunation[MEDKIT] <= 0;
    if (inv->cur_index == MEDKIT && no_medkit)
        inv->cur_index++;
    if (inv->cur_index > MEDKIT)
        inv->cur_index = KNIFE;
}

void handle_inventory_event(inventory_t *inventory, sfEvent *event)
{
    bool p_5;

    if (!inventory || !event)
        return;
    p_5 = event->type == sfEvtKeyPressed &&
        (event->key.code == sfKeyNum5 || event->key.code == sfKeyLBracket);
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyNum1)
        inventory->cur_index = KNIFE;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyNum2)
        inventory->cur_index = GUN;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyNum3)
        inventory->cur_index = MP5;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyApostrophe)
        inventory->cur_index = SPECIAL;
    if (p_5 && inventory->indexes[MEDKIT] == MEDKIT &&
        inventory->cur_ammunation[MEDKIT] > 0)
        inventory->cur_index = MEDKIT;
    handle_inventory_joystick(inventory, event);
}

static bool is_shoot_pressed(void)
{
    bool shoot_pressed = sfMouse_isButtonPressed(sfMouseLeft);

    if (sfJoystick_isConnected(0) && (sfJoystick_isButtonPressed(0, 5) ||
            sfJoystick_getAxisPosition(0, sfJoystickZ) > 50.f))
        shoot_pressed = true;
    return shoot_pressed;
}

static void handle_reload_event(global_t *glb, sfEvent *event)
{
    bool r_pressed;
    bool pad_x_pressed;

    if (!glb || !glb->game || !event)
        return;
    r_pressed = event->type == sfEvtKeyPressed &&
        event->key.code == sfKeyR;
    pad_x_pressed = event->type == sfEvtJoystickButtonPressed &&
        event->joystickButton.button == 2;
    if ((r_pressed || pad_x_pressed) && glb->game->shoot_info.reload_delay !=
        glb->game->weapon[TYPE].reload_delay && INV_AMMUNATION > 0) {
        glb->game->shoot_info.reload_delay =
            glb->game->weapon[TYPE].reload_delay;
        glb->game->shoot_info.reload = true;
    }
}

void handle_weapon_event(global_t *glb, sfEvent *event)
{
    if (!glb || !glb->game)
        return;
    if (glb->lighter_active)
        return;
    if (is_shoot_pressed() &&
        glb->game->shoot_info.shoting_delay <= 0) {
        if (TYPE == MEDKIT && INV_AMMUNATION <= 0)
            return;
        if ((TYPE == KNIFE || TYPE == SPECIAL || TYPE == MEDKIT) ||
            glb->game->shoot_info.reload == false)
            glb->game->shoot_info.is_shoting = true;
    }
    handle_reload_event(glb, event);
}

static void handle_pause_buttons(global_t *glb, scene_type_t *next_scene,
    sfEvent *event)
{
    if (is_text_clicked(glb->game->pause_resume, event)) {
        glb->game->paused = false;
        sfRenderWindow_setMouseCursorVisible(glb->window, false);
    }
    if (is_text_clicked(glb->game->pause_settings, event)) {
        glb->game->in_settings = true;
        init_settings_texts(glb);
    }
    if (is_text_clicked(glb->game->pause_main_menu, event))
        *next_scene = SCENE_MAIN_MENU;
}

static void handle_pause_menu_events(global_t *glb, scene_type_t *next_scene,
    sfEvent *event)
{
    scene_type_t dummy = SCENE_GAME;

    if (glb->game->in_settings) {
        handle_settings_event(glb, event, &dummy);
        if (dummy == SCENE_MAIN_MENU) {
            glb->game->in_settings = false;
            destroy_settings_texts(glb);
        }
    } else {
        handle_pause_buttons(glb, next_scene, event);
    }
    if (is_text_clicked(glb->game->save_text, event)) {
        *next_scene = SCENE_SAVE;
    }
}

static void handle_escape(global_t *glb)
{
    if (glb->game->in_settings) {
        glb->game->in_settings = false;
        destroy_settings_texts(glb);
    } else {
        glb->game->paused = !glb->game->paused;
        sfRenderWindow_setMouseCursorVisible(glb->window,
            glb->game->paused);
    }
}

static void handle_in_game_events(global_t *glb, sfEvent *event)
{
    bool f_p = event->type == sfEvtKeyPressed && event->key.code == sfKeyF;
    bool y_p = event->type == sfEvtJoystickButtonPressed &&
        event->joystickButton.button == 3;

    if (f_p || y_p)
        glb->lighter_active = !glb->lighter_active;
    handle_shop_event(glb, event);
    if (!SHOP.in_shop) {
        handle_inventory_event(glb->game->inventory, event);
        handle_weapon_event(glb, event);
        handle_items_event(glb->game->items.items_list, event, glb);
    }
}

void handle_game_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene)
{
    bool esc_pressed;
    bool start_pressed;

    if (!glb || !glb->game || !event || !next_scene)
        return;
    if (glb->player.health <= 0) {
        handle_game_over_event(glb, event, next_scene);
        return;
    }
    esc_pressed = event->type == sfEvtKeyPressed &&
        event->key.code == sfKeyEscape;
    start_pressed = event->type == sfEvtJoystickButtonPressed &&
        event->joystickButton.button == 7;
    if (esc_pressed || start_pressed)
        handle_escape(glb);
    if (glb->game->paused) {
        handle_pause_menu_events(glb, next_scene, event);
        return;
    }
    handle_in_game_events(glb, event);
}
