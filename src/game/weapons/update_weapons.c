/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** update_weapons
*/

#include "game.h"

void update_rect(weapon_t *weapon, global_t *glb)
{
    if (weapon[TYPE].sprite->rect.left > 0) {
        weapon[TYPE].sprite->rect.left += weapon[TYPE].rect_offset;
        if (weapon[TYPE].sprite->rect.left >= weapon[TYPE].rect_max_offset)
            weapon[TYPE].sprite->rect.left = 0;
        sfSprite_setTextureRect(weapon[TYPE].sprite->sprite,
            weapon[TYPE].sprite->rect);
    }
}

static void add_ammuantion(global_t *glb)
{
    int cur_ammu = WPN_AMMUNATION;

    for (; cur_ammu < CUR_WEAPON.max_ammunation && INV_AMMUNATION > 0;
        cur_ammu++) {
        INV_AMMUNATION--;
        WPN_AMMUNATION++;
    }
}

static void update_reload_rect(game_t *game, global_t *glb, sfVector2u *size)
{
    if (game->weapon[TYPE].reload_sprite) {
        *size = sfTexture_getSize(game->weapon[TYPE].reload_sprite->texture);
        game->weapon[TYPE].reload_sprite->rect.left +=
            game->weapon[TYPE].reload_sprite->rect.width;
        if (game->weapon[TYPE].reload_sprite->rect.left >= (int)size->x)
            game->weapon[TYPE].reload_sprite->rect.left = 0;
        sfSprite_setTextureRect(game->weapon[TYPE].reload_sprite->sprite,
            game->weapon[TYPE].reload_sprite->rect);
    }
}

void update_reload(game_t *game, global_t *glb)
{
    sfVector2u size;

    if (game->shoot_info.reload == true) {
        if (!game->weapon[TYPE].reload_sprite)
            game->weapon[TYPE].sprite->rect.left = -500;
        if (game->shoot_info.reload_delay == game->weapon[TYPE].reload_delay &&
            game->weapon[TYPE].sounds && game->weapon[TYPE].sounds[RELOAD])
            sfSound_play(game->weapon[TYPE].sounds[RELOAD]->sound);
        game->shoot_info.reload_delay -= 0.1;
        update_reload_rect(game, glb, &size);
        if (game->shoot_info.reload_delay <= 0) {
            game->shoot_info.reload = false;
            add_ammuantion(glb);
            game->weapon[TYPE].sprite->rect.left = 0;
            sfSprite_setTextureRect(game->weapon[TYPE].sprite->sprite,
                game->weapon[TYPE].sprite->rect);
        }
    }
}

static void handle_shooting(game_t *game, global_t *glb)
{
    if (game->weapon[TYPE].sounds && game->weapon[TYPE].sounds[SHOOT])
        sfSound_play(game->weapon[TYPE].sounds[SHOOT]->sound);
    game->shoot_info.shoting_delay = game->weapon[TYPE].shoting_delay;
    game->weapon[TYPE].sprite->rect.left = game->weapon[TYPE].rect_offset;
    sfSprite_setTextureRect(game->weapon[TYPE].sprite->sprite,
        game->weapon[TYPE].sprite->rect);
    sfClock_restart(game->clock);
    if (TYPE != KNIFE && TYPE != SPECIAL && TYPE != MEDKIT)
        WPN_AMMUNATION--;
    if (TYPE == MEDKIT)
        INV_AMMUNATION--;
}

static void exec_shoot(game_t *game, global_t *glb)
{
    if (WPN_AMMUNATION != 0 || TYPE == KNIFE || TYPE == SPECIAL ||
        TYPE == MEDKIT) {
        player_shoot(glb);
        handle_shooting(game, glb);
    } else {
        if (game->weapon[TYPE].sounds && game->weapon[TYPE].sounds[DRY_FIRE])
            sfSound_play(game->weapon[TYPE].sounds[DRY_FIRE]->sound);
        game->shoot_info.shoting_delay = 0.8;
        game->weapon[TYPE].sprite->rect.left = game->weapon[TYPE].dry_jump;
        sfSprite_setTextureRect(game->weapon[TYPE].sprite->sprite,
            game->weapon[TYPE].sprite->rect);
        sfClock_restart(game->clock);
    }
}

void update_shoot(game_t *game, global_t *glb)
{
    game->shoot_info.shoting_delay -= 0.1;
    if (game->shoot_info.is_shoting == true) {
        if (game->shoot_info.shoting_delay <= 0) {
            exec_shoot(game, glb);
        }
        game->shoot_info.is_shoting = false;
    }
}

static void check_medkit_depletion(global_t *glb)
{
    inventory_t *inv = glb->game->inventory;

    if (inv->cur_ammunation[MEDKIT] > 0 ||
        glb->game->shoot_info.shoting_delay > 0)
        return;
    inv->indexes[MEDKIT] = KNIFE;
    if (inv->cur_index != MEDKIT)
        return;
    if (inv->indexes[MP5] == MP5)
        inv->cur_index = MP5;
    else if (inv->indexes[GUN] == GUN)
        inv->cur_index = GUN;
    else
        inv->cur_index = KNIFE;
}

void update_weapon_actions(global_t *glb)
{
    sfTime time = sfClock_getElapsedTime(glb->game->cooldown);
    float second = time.microseconds / 1000000.;

    if (second >= 0.1) {
        update_shoot(glb->game, glb);
        update_reload(glb->game, glb);
        sfClock_restart(glb->game->cooldown);
    }
    time = sfClock_getElapsedTime(glb->game->clock);
    second = time.microseconds / 1000000.;
    if (second >= glb->game->weapon[TYPE].speed_rect) {
        update_rect(glb->game->weapon, glb);
        sfClock_restart(glb->game->clock);
    }
    check_medkit_depletion(glb);
}
