/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** update_cinematic.c
*/

#include "wolf.h"

void launch_text(global_t *glb, const char *str)
{
    strcpy(glb->target_text, str);
    glb->text_index = 0;
    sfClock_restart(glb->typewriter_clock);
}

void manage_fade(global_t *glb)
{
    if ((glb->cinematic_step == 7 ||
            ((glb->daughter_caught || glb->daughter_killed) &&
                glb->cinematic_step == 4))
        && glb->fade_alpha < 255) {
        glb->fade_alpha += 3;
        if (glb->fade_alpha > 255)
            glb->fade_alpha = 255;
    }
}

void write_text(global_t *glb)
{
    if (glb->cinematic_step == 1)
        launch_text(glb, "You wake up...\n"
            "in a ruined hospital.");
    if (glb->cinematic_step == 2)
        launch_text(glb, "The last thing you "
            "remember\nis a car accident...");
    if (glb->cinematic_step == 3)
        launch_text(glb, "with your daughter.");
    if (glb->cinematic_step == 4)
        launch_text(glb, "You hear screams\n"
            "and growls in the corridors.");
    if (glb->cinematic_step == 5)
        launch_text(glb, "You must find her.");
    if (glb->cinematic_step == 6)
        launch_text(glb, "You must find her.\n"
            "And get out of this place.");
    else if (glb->cinematic_step == 7)
        glb->end_cinematic = true;
}

void write_text_animation(global_t *glb)
{
    float type_time;

    if (glb->typewriter_clock) {
        type_time = sfTime_asSeconds
            (sfClock_getElapsedTime(glb->typewriter_clock));
        if (type_time > 0.05f && glb->target_text[glb->text_index] != '\0') {
            glb->current_text[glb->text_index] =
                glb->target_text[glb->text_index];
            glb->text_index++;
            glb->current_text[glb->text_index] = '\0';
            sfText_setString(glb->cinematic_txt->text, glb->current_text);
            sfClock_restart(glb->typewriter_clock);
        }
    }
}

static void write_text_end(global_t *glb)
{
    if (glb->cinematic_step == 1)
        launch_text(glb, "You've always been my weakness.\n");
    if (glb->cinematic_step == 2)
        launch_text(glb, "Until my very last breath.\n");
    if (glb->cinematic_step == 3)
        launch_text(glb, "I love you.\n");
}

static void return_to(global_t *glb, float seconds)
{
    if (glb->cinematic_step == 3 && seconds > 4.0f) {
        glb->cinematic_step++;
        sfClock_restart(glb->cinematic_clock);
    }
    else if (glb->cinematic_step == 4 && glb->fade_alpha >= 255)
        glb->end_cinematic = true;
}

static void write_text_killed(global_t *glb)
{
    if (glb->cinematic_step == 1)
        launch_text(glb, "I went through hell to find you...\n");
    if (glb->cinematic_step == 2)
        launch_text(glb, "and in the end, it was me who sent you there.\n");
    if (glb->cinematic_step == 3)
        launch_text(glb, "Rest in peace, my angel.\n");
}

static void update_cin_end(global_t *glb, float seconds)
{
    if (seconds > 2.5f && glb->cinematic_step < 3) {
        glb->cinematic_step++;
        sfClock_restart(glb->cinematic_clock);
        if (glb->daughter_caught)
            write_text_end(glb);
        if (glb->daughter_killed)
            write_text_killed(glb);
    }
    return_to(glb, seconds);
}

void update_cinematic(global_t *glb, sfEvent *event)
{
    float seconds = sfTime_asSeconds(sfClock_getElapsedTime
        (glb->cinematic_clock));

    if (glb->daughter_caught || glb->daughter_killed)
        update_cin_end(glb, seconds);
    else if (seconds > 2.5f && glb->cinematic_step < 7) {
        glb->cinematic_step++;
        sfClock_restart(glb->cinematic_clock);
        write_text(glb);
    }
    write_text_animation(glb);
    manage_fade(glb);
}
