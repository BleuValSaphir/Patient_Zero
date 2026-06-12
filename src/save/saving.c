/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** save
*/

#include "wolf.h"

void save_game(global_t *glb, char *save_name)
{
    FILE *fd;
    char path[256];

    if (!glb)
        return;
    mkdir("saves_wolf3d", 0755);
    sprintf(path, "saves_wolf3d/%s", save_name);
    fd = fopen(path, "w+");
    if (fd == NULL)
        return;
    fprintf(fd, "%d\n%d\n", glb->map_height, glb->map_width);
    for (int i = 0; i < glb->map_height; i++) {
        for (int j = 0; j < glb->map_width; j++) {
            fprintf(fd, "%d,", glb->copy_map[i][j]);
        }
        if (i != glb->map_height - 1)
            fprintf(fd, "\n");
    }
    fclose(fd);
}

void handle_save_event(global_t *glb, sfEvent *event,
    scene_type_t *next_scene)
{
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
        *next_scene = SCENE_PAUSE;
    if (glb->ipt->is_writing == false) {
        strcat(glb->ipt->buffer, ".save");
        save_game(glb, glb->ipt->buffer);
        *next_scene = SCENE_MAIN_MENU;
        glb->ipt->is_writing = true;
    }
    if (input_function(glb, event) == true)
        return;
    sfText_setString(glb->ipt->text_display, glb->ipt->buffer);
}
