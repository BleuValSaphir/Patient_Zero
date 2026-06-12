/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** ending_destroy
*/

#include "wolf.h"

void free_input(input_t *ipt)
{
    if (!ipt)
        return;
    if (ipt->buffer)
        free(ipt->buffer);
    if (ipt->text_display)
        sfText_destroy(ipt->text_display);
    if (ipt->font)
        sfFont_destroy(ipt->font);
    free(ipt);
}

static void destroy_ending_sounds(global_t *glb)
{
    if (glb->menu_sound)
        destroy_sound(glb->menu_sound);
    if (glb->game_music)
        destroy_sound(glb->game_music);
    if (glb->goodbye_sound)
        destroy_sound(glb->goodbye_sound);
    if (glb->epilogue_sound)
        destroy_sound(glb->epilogue_sound);
}

void destroy_all(global_t *glb)
{
    destroy_ending_sounds(glb);
    sfRenderWindow_destroy(glb->window);
    if (glb->fps.clock)
        sfClock_destroy(glb->fps.clock);
    if (glb->render_clock)
        sfClock_destroy(glb->render_clock);
    if (glb->ipt)
        free_input(glb->ipt);
    if (glb->instruction)
        destroy_text(glb->instruction);
    if (glb->copy_map) {
        for (int i = 0; i < MAP_HEIGHT; i++)
            free(glb->copy_map[i]);
        free(glb->copy_map);
    }
}
