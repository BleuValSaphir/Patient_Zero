/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** init_sound
*/

#include "utils.h"

void destroy_sound(sound_effect_t *sound)
{
    if (!sound)
        return;
    if (sound->buff)
        sfSoundBuffer_destroy(sound->buff);
    if (sound->sound)
        sfSound_destroy(sound->sound);
    free(sound);
}

sound_effect_t *set_sound(char *filepath, float volume)
{
    sound_effect_t *sound = NULL;

    if (!filepath)
        return NULL;
    sound = malloc(sizeof(*sound) * 1);
    if (!sound)
        return NULL;
    sound->buff = sfSoundBuffer_createFromFile(filepath);
    sound->sound = sfSound_create();
    if (!sound->buff || !sound->sound) {
        destroy_sound(sound);
        return NULL;
    }
    sfSound_setBuffer(sound->sound, sound->buff);
    sfSound_setVolume(sound->sound, volume);
    sound->played = false;
    sound->delay = 0.0f;
    return sound;
}
