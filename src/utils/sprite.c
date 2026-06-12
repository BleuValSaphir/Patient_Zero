/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** sprite
*/

#include "utils.h"

void destroy_sprite(sprite_t *sprite)
{
    if (!sprite)
        return;
    if (sprite->sprite)
        sfSprite_destroy(sprite->sprite);
    if (sprite->texture)
        sfTexture_destroy(sprite->texture);
    if (sprite->clock)
        sfClock_destroy(sprite->clock);
    free(sprite);
}

void init_info(const sfVector2f *scale, const sfVector2f *origin,
    const sfVector2f *pos, sprite_t *sprite)
{
    if (origin)
        sfSprite_setOrigin(sprite->sprite, *origin);
    if (scale)
        sfSprite_setScale(sprite->sprite, *scale);
    if (pos)
        sfSprite_setPosition(sprite->sprite, *pos);
}

sprite_t *set_sprite(char *filepath, const sfVector2f *scale,
    const sfVector2f *origin, const sfVector2f *pos)
{
    sprite_t *sprite = malloc(sizeof(*sprite) * 1);

    if (!filepath || !sprite)
        exit(ERROR);
    sprite->sprite = sfSprite_create();
    sprite->texture = sfTexture_createFromFile(filepath, NULL);
    sprite->clock = sfClock_create();
    sprite->rect = (sfIntRect){0, 0, 0, 0};
    if (!sprite->sprite || !sprite->texture) {
        destroy_sprite(sprite);
        exit(ERROR);
    }
    sfTexture_setSmooth(sprite->texture, sfFalse);
    sfSprite_setTexture(sprite->sprite, sprite->texture, sfTrue);
    init_info(scale, origin, pos, sprite);
    return sprite;
}
