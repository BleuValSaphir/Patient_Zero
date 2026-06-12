/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** destroy_cinematic.c
*/

#include "wolf.h"

void destroy_cinematic(global_t *glb)
{
    if (glb->cinematic_txt)
        destroy_text(glb->cinematic_txt);
    if (glb->cinematic_clock)
        sfClock_destroy(glb->cinematic_clock);
    if (glb->typewriter_clock)
        sfClock_destroy(glb->typewriter_clock);
}
