/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** config.c
*/

#include "wolf.h"

void save_settings(global_t *glb)
{
    FILE *file = fopen("config.cfg", "w");

    if (!glb)
        return;
    if (!file)
        return;
    fprintf(file, "volume=%d\n", glb->volume);
    fprintf(file, "fps_limit=%d\n", glb->fps_limit);
    fprintf(file, "is_fullscreen=%d\n", glb->is_fullscreen);
    fprintf(file, "mouse_sens=%.2f\n", glb->mouse_sens);
    fprintf(file, "headbobbing=%d\n", glb->headbobbing);
    fprintf(file, "is_qwerty=%d\n", glb->is_qwerty);
    fclose(file);
}

static void assign_setting(global_t *glb, char *key, float val)
{
    if (!glb || !key)
        return;
    if (strcmp(key, "volume") == 0)
        glb->volume = (int)val;
    if (strcmp(key, "fps_limit") == 0)
        glb->fps_limit = (int)val;
    if (strcmp(key, "is_fullscreen") == 0)
        glb->is_fullscreen = (int)val;
    if (strcmp(key, "mouse_sens") == 0)
        glb->mouse_sens = val;
    if (strcmp(key, "headbobbing") == 0)
        glb->headbobbing = (int)val;
    if (strcmp(key, "is_qwerty") == 0)
        glb->is_qwerty = (int)val;
}

void load_settings(global_t *glb)
{
    FILE *file = fopen("config.cfg", "r");
    char line[256];
    char key[128];
    float val;

    if (!glb)
        return;
    if (!file)
        return;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%127[^=]=%f", key, &val) == 2)
            assign_setting(glb, key, val);
    }
    fclose(file);
}
